#include "Huffman.h"


class Node{
    private:
        char asc;
        int freq;
        string enc;

    public:

        Node* left;
        Node* right;
        Node(char a, int f);
        Node(){};
        Node(const Node &tmp);
        bool operator<(const Node &) const;
        bool is_leaf();
        char get_asc() const{return asc;};
        string get_string ()const;

        int get_freq() const{return freq;};
        int set_freq(int freq) {this->freq = freq;}

        // set the encoding for this node
        void set_enc(string tmp){this->enc = tmp;}
        
};

Node::Node(char a, int f){
    asc=a;
    freq=f;
    left=NULL;
    right=NULL;
    set_enc("");
}

Node::Node(const Node &tmp){
    asc = tmp.asc;
    freq = tmp.freq;
    left= tmp.left;
    right = tmp.right;
}

// define the priority
bool Node::operator < (const Node & right) const{
    // lower frequncy has higher priority
    return (this->get_freq() > right.get_freq());
}

bool Node::is_leaf(){
    if(left == NULL && right == NULL)
        return true;
    else
        return false;
}


string Node::get_string() const{
    string outstring;
    if(asc == 10){
            outstring = "LF";
     }else
            outstring = asc;
     return outstring;
}



/*
 * read frequency and contruct the priority queue 
 * input:
 */

// return: the number of character types
int read_freq(string freq_path, priority_queue <Node> &pq){
    ifstream ifs(freq_path, ifstream::out);
    string a;
    char asc;
    int freq;
    int count = 0;
    while(ifs >> a >> freq){
        cout << "char: " << a << " has a frequency of " << freq << endl;
        // create  a new node a should use int here
        if(a.length()== 1)
            asc = a.c_str()[0];

        else if(a == "LF")
            asc = 10;

        else{
            cout << "invalid input, currently only LF and printable characters are supported " << endl;
            exit(-1);
        }
        Node tmp = Node(asc, freq);
        pq.push(tmp);
        count++;
    }
    return count;
}

// construct the huffman tree
Node* huffman(priority_queue <Node> &pq){
    // size of all elements
    int n = pq.size();
    int i;
    for(i = 0; i< n-1; i++){
        //allocate a new node
        Node tmp = Node();

        // error here, when copy the node its children are lost
        tmp.left = new Node(pq.top());
        //cout << "try to pop " << tmp.left->get_freq();
        pq.pop();

        tmp.right = new Node(pq.top());

        //cout << "try to pop " << tmp.right->get_freq();
        pq.pop();

        tmp.set_freq(tmp.left->get_freq() + tmp.right->get_freq());
#ifdef debug
        cout << "get node with freq " << tmp.get_freq() << " by adding " 
            << tmp.left->get_freq()<<"(" << tmp.left->get_string()<<")" 
            <<" and "
            << tmp.right->get_freq()<< "(" <<tmp.right->get_string() << ")" <<endl;
#endif
        pq.push(tmp);
    }
    
#ifdef debug
    cout << "huffman tree constructed from " << n << " nodes" << endl;;
#endif
    return (Node*)addressof(pq.top());
}


/*
 *  recursively print the tree using preoder 
 *  input: 
 *      root: the root of current huffman (sub)tree
 *      enc: the output encoding of all the words
 *      ofs: output stream
 *      level: current level in the tree
 */
void print_tree(Node* root, string enc,map<char, string> &my_dic, int level=0)
{
    char asc;
    string outstring;
    // External nodes are not printed.
    if (root == NULL) {
        return;
    }

    if (root->is_leaf()) {
        // output the asc and also binary encoding
        //cout << "this is leaf in level"<< level << endl;

        // this is a line
        outstring = root->get_string() + " " + enc;
        asc = root->get_asc();
        
        // save it to dictionay
        my_dic.insert(pair<char, string>(asc, outstring));
        

        cout << root->get_string() << " has encoding of " << enc << endl;

    } else {
        // Print left and right subtrees with the appropriate prefix, and
        // increased indent (by INDENT_SIZE).
        //
        //cout << "freq " << root->get_freq()<< " in level" << level << endl;

        print_tree(root->left, enc + "0",my_dic, level+1);
        print_tree(root->right, enc +"1",my_dic, level+1);
    }
}

/*
 * write current encoding into file
 * input:
 *      head: the root of huffman tree
 *      code_path: the path of output path
 */
void write_code(Node *head, string code_path){

    ofstream os(code_path);

    // store all the encoding in a dictionary
    map<char, string> my_dic;

    // based on preorder traversal
    print_tree(head, "", my_dic);

    // write all the entries ordering by asc code
    for(map<char, string>::iterator it = my_dic.begin(); it!=my_dic.end(); it++){
        os << it->second << endl;
    }
    
    os.close();
    cout << endl <<"*****result has been saved in " << code_path << endl;
}


/*
 * print priority queue,
 * for debugging use
 */
void print_queue(priority_queue <Node> & q) {
        

        cout << "queue has size of " << q.size();
        cout << "the queue is: \t";
        while(!q.empty()) {
                    std::cout << q.top().get_freq() << " ";
                            q.pop();
                                }
            std::cout << '\n';
}

/* 
 * main routine
 */ 
int main(){
    string freq_path = FREQ_PATH;
    string code_path = CODE_PATH;

    // store word dictionay and frequency seprately
    priority_queue <Node> pq;

    // read freq into priority queue
    cout << "******start read frequecy file from path " << freq_path<< endl;
    read_freq(freq_path, pq);

    
    //print_queue(pq);

    // generate the huffman tree


    cout << endl << endl << "******start to build huffman tree" << endl;
    Node* head = huffman(pq);


    cout << endl << endl << "******start to output all the codes" << endl;
    write_code(head, code_path);

    return 0;
}
    
