/*-------------------------------------------------------------------------
 *
 *   FILE
 *	connection.cxx
 *
 *   DESCRIPTION
 *      implementation of the pqxx::connection and sibling classes.
 *   Different ways of setting up a backend connection.
 *
 * Copyright (c) 2001-2015, Jeroen T. Vermeulen <jtv@xs4all.nl>
 *
 * See COPYING for copyright license.  If you did not receive a file called
 * COPYING with this source code, please notify the distributor of this mistake,
 * or contact the author.
 *
 *-------------------------------------------------------------------------
 */
#include "pqxx/compiler-internal.hxx"

#include <stdexcept>

#include "libpq-fe.h"

#include "pqxx/connection"

using namespace std;


pqxx::connectionpolicy::connectionpolicy(const std::string &opts) :
  m_options(opts)
{
}


pqxx::connectionpolicy::~connectionpolicy() PQXX_NOEXCEPT
{
}


pqxx::connectionpolicy::handle
pqxx::connectionpolicy::normalconnect(handle orig)
{
  if (orig) return orig;
  orig = PQconnectdb(options().c_str());
  if (!orig) throw bad_alloc();
  if (PQstatus(orig) != CONNECTION_OK)
  {
    const string msg(PQerrorMessage(orig));
    PQfinish(orig);
    throw broken_connection(msg);
  }
  return orig;
}


pqxx::connectionpolicy::handle
pqxx::connectionpolicy::do_startconnect(handle orig)
{
  return orig;
}

pqxx::connectionpolicy::handle
pqxx::connectionpolicy::do_completeconnect(handle orig)
{
  return orig;
}

pqxx::connectionpolicy::handle
pqxx::connectionpolicy::do_dropconnect(handle orig) PQXX_NOEXCEPT
{
  return orig;
}

pqxx::connectionpolicy::handle
pqxx::connectionpolicy::do_disconnect(handle orig) PQXX_NOEXCEPT
{
  orig = do_dropconnect(orig);
  if (orig) PQfinish(orig);
  return 0;
}


bool pqxx::connectionpolicy::is_ready(handle h) const PQXX_NOEXCEPT
{
  return h != 0;
}


pqxx::connectionpolicy::handle
pqxx::connect_direct::do_startconnect(handle orig)
{
  if (orig) return orig;
  orig = normalconnect(orig);
  if (PQstatus(orig) != CONNECTION_OK)
  {
    const string msg(PQerrorMessage(orig));
    do_disconnect(orig);
    throw broken_connection(msg);
  }
  return orig;
}


pqxx::connectionpolicy::handle
pqxx::connect_lazy::do_completeconnect(handle orig)
{
  return normalconnect(orig);
}


pqxx::connect_async::connect_async(const std::string &opts) :
  connectionpolicy(opts),
  m_connecting(false)
{
}

pqxx::connectionpolicy::handle
pqxx::connect_async::do_startconnect(handle orig)
{
  if (orig) return orig;	// Already connecting or connected
  m_connecting = false;
  orig = PQconnectStart(options().c_str());
  if (!orig) throw bad_alloc();
  if (PQstatus(orig) == CONNECTION_BAD)
  {
    do_dropconnect(orig);
    throw broken_connection(string(PQerrorMessage(orig)));
  }
  m_connecting = true;
  return orig;
}


pqxx::connectionpolicy::handle
pqxx::connect_async::do_completeconnect(handle orig)
{
  const bool makenew = !orig;
  if (makenew) orig = do_startconnect(orig);
  if (!m_connecting) return orig;

  // Our "attempt to connect" state ends here, for better or for worse
  m_connecting = false;

  PostgresPollingStatusType pollstatus = PGRES_POLLING_WRITING;

  do
  {
    switch (pollstatus)
    {
    case PGRES_POLLING_FAILED:
      if (makenew) do_disconnect(orig);
      throw broken_connection(string(PQerrorMessage(orig)));

    case PGRES_POLLING_READING:
      internal::wait_read(orig);
      break;

    case PGRES_POLLING_WRITING:
      internal::wait_write(orig);
      break;

    case PGRES_POLLING_OK:
      break;

    default:
      // Meaningless, really, but deals with the obsolete PGRES_POLLING_ACTIVE
      // without requiring it to be defined.
      break;
    }
    pollstatus = PQconnectPoll(orig);
  } while (pollstatus != PGRES_POLLING_OK);

  return orig;
}


pqxx::connectionpolicy::handle
pqxx::connect_async::do_dropconnect(handle orig) PQXX_NOEXCEPT
{
  m_connecting = false;
  return orig;
}


bool pqxx::connect_async::is_ready(handle h) const PQXX_NOEXCEPT
{
  return h && !m_connecting;
}

