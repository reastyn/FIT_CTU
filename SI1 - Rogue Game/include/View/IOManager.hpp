#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <cstdio>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "common.hpp"

#include "imgui-SFML.h"
#include "imgui.h"

namespace RG{ namespace View {

    //! \class IOManager
    /*!
     * \brief
     * This class provides the service of mapping keyboard keys.
     *
     * It enables to map any keyboard key to different key or to map more than one keyboard keys to one keyboard key.
     * */
    class IOManager{

        public:

            //! IOManager class constructor.
            /*!
             * Method may take two parameters:
             * @param dir Storage directory.
             * @param fileName Storage file name.
             */
            IOManager(std::string dir = ".", std::string fileName = "mapping.txt");

            /// IOManager class destructor.
            ~IOManager();

            //! Method for getting the key to which is the key from argument mapped.
            /*!
             * Method takes one parameter:
             * @param key Key code.
             * @return Returns mapped key.
             */
            sf::Keyboard::Key GetMapped(sf::Keyboard::Key key) const;

            //! Method for mapping key toMap to key mapRes.
            /*!
             * Method takes two parameters:
             * @param toMap Key to be remapped.
             * @param mapRes Key to which map.
             */
            void MapKey(sf::Keyboard::Key toMap, sf::Keyboard::Key mapRes);

            /// Method for drawing IOManager interface.
            void Draw();

            /// Method for setting default key mapping.
            void SetDefaultKeys();

            //! Method for setting the storage directory.
            /*!
             * Method takes one parameter:
             * @param dir Storage directory.
             */
            void SetStorageDir(std::string dir);

            //! Method for setting the storage file.
            /*!
             * Method takes one parameter:
             * @param fileName Storage file name.
             */
            void SetFile(std::string fileName);

        private:

            /// Method for serializing keyboard key mapping.
            void Serialize();

            /// Method for deserializing keyboard key mapping from file.
            void Deserialize();

            //! Method for opening the storage file stream.
            /*!
             * @return Returns true if the file was open successfully, else it returns false.
             */
            bool Open();

            //! Method for closing the storage file stream.
            /*!
             * @return Returns true if the file was closed successfully, else it return false.
             */
            bool Close();

            //! Method for testing if the file exists.
            /*!
             * Method takes one parameter:
             * @param fileName File name.
             * @return Returns true if the file exists, else it returns false.
             */
            bool FileExists(std::string fileName);

            /// Member variable representing mapping of keys.
            std::vector<sf::Keyboard::Key> m_KeyArr;

            /// Member variable representing keys description for interface
            const char * m_Keys[101] = {
                    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
                    "U", "V", "W", "X", "Y", "Z", "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8",
                    "Num9", "Escape", "LControl", "LShift", "LAlt", "LSystem", "RControl", "RShift", "RAlt",
                    "RSystem", "Menu", "LBracket", "RBracket", "SemiColon", "Comma", "Period", "Quote", "Slash",
                    "BackSlash", "Tilde", "Equal", "Dash", "Space", "Return", "BackSpace", "Tab", "PageUp", "PageDown",
                    "End", "Home", "Insert", "Delete", "Add", "Subtract", "Multiply", "Divide", "Left", "Right", "Up",
                    "Down", "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7",
                    "Numpad8", "Numpad9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
                    "F13", "F14", "F15", "Pause"
            };

            /// Member variable representing the storage file stream
            std::fstream m_Stream;

            /// Member variable representing the storage directory
            std::string m_StorageDir;

            /// Member variable representing the storage file
            std::string m_File;

    };

} }
