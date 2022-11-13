#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

int treeH(Node * root)
{
    int LST = 0;
    int RST = 0;
    if(root -> left != nullptr){
        LST = treeH(root -> left);

    }
    if(root -> right != nullptr){
       RST =  treeH(root -> right);

    }
    if(root -> right == nullptr && root -> left == nullptr){
        return 1;
    }else{
        if(LST > RST){
            return (1 + LST);
        }
        else{
            return (1 + RST);
        }  
    }
    



}
bool equalPaths(Node * root)
{
    // Add your code below

    int valL = 0;
    int valR = 0;

    if(root -> left != nullptr){
      valL = treeH(root -> left);
    }
    if(root -> right != nullptr){
      valR = treeH(root -> right);
    }

    if(valL == valR){
      return true;
    }
    return false;


    
    

}

