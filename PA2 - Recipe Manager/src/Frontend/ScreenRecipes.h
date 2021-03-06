//
// Created by pjahoda on 5/7/17.
//

#ifndef RECIPE_MANAGER_SCREENRECIPES_H
#define RECIPE_MANAGER_SCREENRECIPES_H

#include "ScreenIngredients.h"

class ScreenRecipes : public ScreenIngredients
{
public:
    ScreenRecipes();

    ~ScreenRecipes();

    //int Run(const map<string, string> & mapa, vector<string> &){return 0;};
    int Run() { return 0; }

    void Run(string &, string &) {};

    void AssignData(Data &data) {};

    //void KeyUp(){};
    //void KeyDown(){};
    void KeyLeft();

    void KeyRight();

    //void Backspace(){};
    void Enter();

    //void OtherKey(){};
    void PrintTextInfoForUser() const;

    void SetVariables();

    bool AreYouRecipeScreen() { return true; }

protected:
private:
    void ChangeFocus();
};

#endif //RECIPE_MANAGER_SCREENRECIPES_H
