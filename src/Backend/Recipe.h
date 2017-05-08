//
// Created by pjahoda on 5/6/17.
//

#ifndef RECIPE_MANAGER_RECIPE_H
#define RECIPE_MANAGER_RECIPE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Recipe
{
public:
    Recipe(vector<string> ingredients, vector<int> ingredientWeight, int idRecipe);
    int HowMuchAreRecipesSame(const Recipe &);
    string ToString();
    bool operator==(Recipe & r)
    {
        for(unsigned int i=0;i<this->ingredients.size();i++)
        {
            if(this->ingredients[i]!=r.ingredients[i])
            {
                return false;
            }
            if(this->ingredientWeight[i]!=r.ingredientWeight[i])
            {
                return false;
            }
        }
        return true;
    }
    ~Recipe();

protected:
private:
    vector<string> ingredients;
    vector<int> ingredientWeight;
    int idRecipe;
};

#endif //RECIPE_MANAGER_RECIPE_H
