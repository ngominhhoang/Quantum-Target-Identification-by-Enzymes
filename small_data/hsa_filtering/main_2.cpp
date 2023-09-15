//
//  main.cpp
//  TIE_Exhaustive_Search
//
//  Created by Ngo Minh Hoang on 24/12/2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,bool> pi;

class Item {
public:
    string state;
    int k;
    int d;
    bool removed;
    Item(string state, int k, int d, bool removed) {
        this->state = state;
        this->k = k;
        this->d = d;
        this->removed = removed;
    }
};

class Node {
public:
    int type;
    string name;
    int index;
    vector<Node*>* successor_list;
    vector<Node*>* predecessor_list;
    Node(int type, string name, int index) {
        this->type = type;
        this->name = name;
        this->index = index;
        this->successor_list = new vector<Node*>();
        this->predecessor_list = new vector<Node*>();
    }
    void append_successor(Node* p) {
        this->successor_list->push_back(p);
    }
    void append_predecessor(Node* p) {
        this->predecessor_list->push_back(p);
    }
};

class Graph {
public:
    vector<Node*>* node_list;
    Graph() {
        this->node_list = new vector<Node*>();
    }
    void append_node(Node* p) {
        this->node_list->push_back(p);
    }
    Node* find_node(string name) {
        for (auto p = this->node_list->begin(); p != this->node_list->end(); ++p) {
            if ((*p)->name == name) {
                return *p;
            }
        }
        return nullptr;
    }
};

int n_enzymes, n_reactions, n_compounds;

string make_zero(int len) {
    string s = "";
    for (int i = 0; i < len; ++i) {
        s = s + '0';
    }
    return s;
}

string make_random(int k, int n) {
    string s = make_zero(n);
    bool check[1001];
    for (int i = 0; i < n; ++i) {
        check[i] = false;
    }
    while (k != 0) {
        int j = rand()%n;
        while (check[j]) {
            j = rand()%n;
        }
        s[j] = '1';
        check[j] = true;
        --k;
    }
    return s;
}

pi bfs(string state, string target, Graph* G) {
    int n_total = n_enzymes+n_reactions+n_compounds;
    bool check[n_total];
    for (int i = 0; i < n_total; ++i) {
        check[i] = true;
    }
    queue<int> q;
    int idx = 0;
    for (int i = 0; i < n_total; ++i) {
        if (G->node_list->at(i)->type == 0){
            if (state[idx] == '1') {
                q.push(i);
                check[i] = false;
            }
            ++idx;
        }
    }
    
    while (!q.empty()) {
        int head_idx = q.front();
        q.pop();
        Node* head = G->node_list->at(head_idx);
        for (auto tail = head->successor_list->begin(); tail != head->successor_list->end(); ++tail) {
            int tail_idx = (*tail)->index;
            int tail_type = (*tail)->type;
            if (check[tail_idx]) {
                if (tail_type == 2) {
                    bool double_check = true;
                    for (auto pre_tail = (*tail)->predecessor_list->begin(); pre_tail != (*tail)->predecessor_list->end(); ++pre_tail) {
                        if (check[(*pre_tail)->index]) {
                            double_check = false;
                            break;
                        }
                    }
                    if (double_check) {
                        check[tail_idx] = false;
                        q.push(tail_idx);
                    }
                } else {
                    check[tail_idx] = false;
                    q.push(tail_idx);
                }
            }
        }
    }
    
    int damage = 0, removal = 0, len_target = 0;
    idx = 0;
    for (int i = 0; i < n_total; ++i) {
        if (G->node_list->at(i)->type == 2){
            if (target[idx] == '1') {
                removal += (check[i] == false);
                ++ len_target;
            } else {
                damage += (check[i] == false);
            }
            idx ++;
        }
    }
    return make_pair(damage, removal == len_target);
}

int branch_and_bound(string target, Graph* G) {
    stack<Item*> st;
    st.push(new Item(make_zero(n_enzymes), 0, 0, false));
    
    int min_damage = 100000000;
    while (!st.empty()) {
        Item* it = st.top();
        st.pop();
        if ((it->removed) || (it->d > min_damage) || (it->k >= n_enzymes)) {
            	delete it;
		continue;
        }
        
        Item* next_it_0 = new Item(it->state, it->k + 1, it->d, it->removed);
        st.push(next_it_0);
        
        string curr_state = it->state;
        curr_state[it->k] = '1';
        pi res = bfs(curr_state, target, G);
        if ((res.first < min_damage) && (res.second)) {
            min_damage = res.first;
            cout << min_damage << endl;
        }
        Item* next_it_1 = new Item(curr_state, it->k + 1, res.first, res.second);
        st.push(next_it_1);
	delete it;
    }
    return min_damage;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    srand (time(NULL));
    string filename = argv[1];
    int step = atoi(argv[2]);
    int num_tests = atoi(argv[3]);
    
    ifstream fi(filename);
    Graph* G = new Graph();
    
    int index = 0;
    for (int t = 0; t < 3; ++t) {
        string s_size;
        int n_size;
        getline(fi, s_size);
        n_size = stoi(s_size);
        if (t == 0) {
            n_enzymes = n_size;
        } else if (t == 1) {
            n_reactions = n_size;
        } else {
            n_compounds = n_size;
        }
        for (int i = 0;i < n_size; ++i) {
            string s_name;
            getline(fi, s_name);
            Node* p = new Node(t, s_name, index);
            G->append_node(p);
            ++index;
        }
    }
    
    string s_size;
    int n_size;
    getline(fi, s_size);
    n_size = stoi(s_size);
    for (int i = 0;i < n_size; ++i) {
        string s_edge, s_node[2];
        s_node[0] = "";
        s_node[1] = "";
        int flag = 0;
        getline(fi, s_edge);
        for (int j = 0; j < s_edge.length(); ++j) {
            if (s_edge[j] != ' ') {
                s_node[flag] = s_node[flag] + s_edge[j];
            } else {
                flag = flag + 1;
            }
        }
        Node* p0 = G->find_node(s_node[0]);
        Node* p1 = G->find_node(s_node[1]);
        p0->append_successor(p1);
        p1->append_predecessor(p0);
    }
    
    int idx = 0;
    string tar[7] = {"C00024", "C00074", "C00036", "C00083", "C05125", "C00256", "C00033"};
    string sta[15] = {"1.1.1.2", "1.1.1.299", "1.1.1.38", "1.1.1.40", "1.1.2.4", "1.2.1.3", "1.2.1.5", "2.3.1.12", "2.7.1.40", "3.1.2.1", "3.1.2.6", "3.6.1.7", "4.1.1.32", "6.2.1.1", "6.4.1.1"};
    string target_ = "", state = "";
    for (int i = 0; i < n_enzymes+n_reactions+n_compounds; ++i) {
        if (G->node_list->at(i)->type == 2){
            string name = G->node_list->at(i)->name;
            char ch = '0';
            for (int j = 0; j < 7; ++j) {
                if (name == tar[j]) {
                    ch = '1';
                }
            }
            target_ = target_ + ch;
            idx ++;
        } else if (G->node_list->at(i)->type == 0) {
            string name = G->node_list->at(i)->name;
            char ch = '0';
            for (int j = 0; j < 15; ++j) {
                if (name == sta[j]) {
                    ch = '1';
                }
            }
            state = state + ch;
        }
    }
    
    int idx_step = 2;
    fstream fo;
    
    while (idx_step < n_compounds) {
        for (int t = 0; t < num_tests; ++t) {
            string target = make_random(idx_step, n_compounds);
            target = target_;
            fo.open("Res_test_"+filename, ofstream::app);
            fo<<"Target_size"<<endl<<idx_step<<endl;
            fo<<"Target"<<endl;
            int idx = 0;
            for (int i = 0; i < n_enzymes+n_reactions+n_compounds; ++i) {
                if (G->node_list->at(i)->type == 2){
                    if (target[idx] == '1') {
                        fo << G->node_list->at(i)->name <<endl;
                    }
                    idx ++;
                }
            }
            clock_t tStart = clock();
            fo<<"Damage"<<endl<<branch_and_bound(target, G)<<endl;
            fo<<"Running_time"<<endl<<(double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;
            fo.close();
        }
        idx_step += step;
    }
    
    return 0;
}
