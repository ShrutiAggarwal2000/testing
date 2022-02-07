#include<iostream>
#include<vector>
#include<string>
#include<queue>
using namespace std;
class Node{
    int data;
    vector<Node*> childs;
    Node(int data){
        this->data = data;
    }
}

// pre order construct
Node* constructGT(vector<int>& arr,int idx){

    Node * root = new Node(arr[idx]);
    while(arr[++idx] != -1){
        Node* child = constructGT(arr,idx);
        root->childs.push_back(child);
    }
    return root;
}

// preoredr traversal of generic tree

void preOrder(Node* node){
    cout<<node->data<<" ";
    for(Node * child:node->childs)
       preOrder(child);
}

// detailed preOrder - with childs of node --- this is not level order .... ////////
void display(Node* node){
    string str;
    str += to_string(node->data) + "-> ";
    for(Node* child: node->childs){
       str += to_string(child->data);
    }
    cout<<str;
    for(Node* child: node->childs){
       display(child);
    }
}

int size(Node* node){
    int size_ = 0;
    for(Node* child: node->childs)
       size_ += size(child);
    return size_ + 1;
}

int height(Node* node){
    int height_ =-1;
    for(Node* child: node->childs)
       height_ = max(height_ , height(child));
    return height_ + 1;
}

void levelOrder(Node* node){
    queue<Node*> que;
    que.push(node);
    while(que.size()!= 0){
        int size = que.size();
        while(size-->0){
            Node* rnode = que.pop();
            cout<<rnode->data<<" ";
            for(Node* child:rnode->childs)
               que.push(child);
        }
        cout<<endl;
    }
}

bool find(Node* root,int ele){
    if(root->data == ele)
        return true;
    bool res = false;
    for(Node* child:root->childs)
        res = res || find(child,ele);
    return res;
}

// root to node path

bool rootToNodePath(Node* node,int ele,vector<int> &path){
    if(node->data == ele){
       path.push_back(ele);
       return ;
    }
    bool res = false;
    path.push_back(node->data);
    for(Node* child:node->childs){
        res = res || rootToNodePath(child,ele,str);
    }
    if(!res)
       path.pop_back();
    return res;
}

public static boolean rootToNodePath(Node root, int data, ArrayList<Node> ans) {
        if (root.val == data) {
            ans.add(root);
            return true;
        }

        boolean res = false;
        for (Node child : root.childs) {
            res = res || rootToNodePath(child, data, ans);
            // if(res) break;
        }

        if (res)
            ans.add(root);

        return res;
    }


// is mirror

bool isMirror(Node* root1 , Node* root2){
    if(root1->data != root2->data || root1->childs.size() != root2->childs.size())
        return false;

    int j = root->childs.size() - 1 ;

    for(int i = 0;i < root->childs.size(); i ++){
        if(!isMirror(root1->childs[i] , root2->childs[j-i]))
           return false;
    }
    return true;
}

// Node* linearizeGT(Node* node){
//     if(node == nullptr || node->childs.size() == 0)
//        return node;

//     else if(node->childs.size() == 1)
//         node->childs.push_back(linearizeGT(node->childs[0]));
//     int n = node->childs.size();

//     else{
//     for(int i =0;i< n ; i++){
//         Node* child1 = linearizeGT(node->childs[i]);
//         Node* child2 = linearizeGT(node->childs[i+1]);

//         node->childs.erase(node->childs.begin()+i+1);
//         node->childs[i] = child1;
//     }
//     }
//     return node;
// }


// easier to handle if starting linearizing from  back
Node* linearizeGt(Node* root){
    if(root->childs.size() == 0)
        return root;

    int n = root->childs.size();
    Node* tail = linearizeGt(root.childs[n-1]);
    for(int i=n-2;i>=0;i--){
        vector<Node*> child = root->childs;
        Node* temp_tail = linearizeGT(child[i]);
        temp_tail->childs.push_back(child[i+1]);
        child.pop_back();
    }
    return tail;
}

Node* linearizeGt(Node* root){
    if(root->childs.size() == 0)
        return root;

    int n = root->childs.size();
    vector<Node*> child = root->child;
    Node* global_tail = linearizeGt(child[0]);
    Node* prev_tail = global_tail;
    while(child.size() != 1){
        global_tail = linearizeGt(child[1]);
        prev_tail->childs.push_back(child[1]);
        // reomve this child
        child.erase(child.begin() + 1);
        prev_tail = global_tail;
    }
    return global_tail;
}

// burning tree =============================================================================


void KDown(Node* root,int time,Node* block,vector<vector<int>> & ans){
    if(root == nullptr || root == block)  return ;

    if(ans.size() == time){
       vector<int> sub;
       ans.push_back(sub);
    }
    ans[time].push_back(node);
    for(Node* child:root->childs)
        KDown(child,time+1,block,ans);
}
void burningTree(Node* root,int data){
    vector<vector<int>>  ans;
    vector<Node*> path = rootToNodePath(root,data);
    Node* block = nullptr;
    for(int i=0;i<path.size();i++){
        KDown(path[i],i,block,ans);
        block = path[i];
    }

    return ans;

}

bool burningTree_(Node* root,int data,int & level,vector<vector<int>> ans){

    if(root->data == data){
        KDown(root,nullptr,0,ans,level);
        level ++;
        return true;   // return 1;
    }

    bool res = false;  // time = -1
    Node* block = nullptr;
    for(Node* child: root->childs){
        res |= burningTree_(child,data,level,ans);
        if(res){     // time = burningTree_(child,data,ans) if  != -1 call KDown(root,child,time,ans)
            KDown(root,child,level,ans);
            level++;   // time ++;
            break;
        }

    }
    return res;
    // can return time also instead of bool != -1 implies true state;
}
