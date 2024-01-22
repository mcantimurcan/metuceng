#include <iostream>
#include <string>
#include "trie.h"
#include "user_interface.h"
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include "bst.h"
#include "movie.h"
#include "user.h"

using namespace std;

/* this is the main file i used to test if it works*/

int main(){
    string key1="titanic";
    string key2="Inception";
    string key3="Jurassic Park";
    string key4="Pulp Fiction";
    string key5="The Dark Knight";
    string key6="Forrest Gump";
    string mov1="titanic";
    string mov2="Inception";
    string mov3="Jurassic Park";
    string mov4="Pulp Fiction";
    string mov5="The Dark Knigh";
    string mov6="Forrest Gump";
    Movie movie1(mov1,3432,331);
    Movie movie2(mov2,342,31231231);
    Movie movie3(mov3,32,3131);
    Movie movie4(mov4,11,3232);
    Movie movie5(mov5,11,3232);
    Movie movie6(mov6,21312,211321);
    BST<Movie> a ,b;
    BST<Movie> *result;
    b.insert(key6,movie6);
    a.insert(key1,movie1);
    a.insert(key2,movie2);
    a.insert(key3,movie3);
    a.insert(key4,movie4);
    a.insert(key5,movie5);
    cout<< "titanic in a is: " << a.search("titanic") << endl;
    //result=a.merge(&b);
    Trie<User> c;
    c.insert("ali");
    c.insert("alper");
    c.insert("alperen");
    c.insert("eren");
    c.insert("Alperen");
    c.insert("alpis");
    c.insert("ata");
    c.insert("atalp");
    c.insert("att");
    c.insert("atapi");
    //c.insert("eren");
    User* user = c.search("atalp");
    
    user->addMovie("titanic",movie1);
    user->addMovie("edsadasray",movie2);
    //user->printMovies();
    c.remove("Berat");
    User* user1 = c.search("alperen");
    user1->addMovie(key6,movie6);
    user1->addMovie(key1,movie1);
    user1->addMovie(key6,movie6);
    user1->addMovie(key2,movie2);
    User* user2 = c.search("ata");
    user2->addMovie(key6,movie6);
    user2->addMovie(key1,movie1);
    user2->addMovie(key4,movie4);
    user2->addMovie(key5,movie5);
    user2->printMovies();
    cout << "\n ************************************\n";
    BST<Movie> *resultEmpty = user2->getMovies()->intersection(user1->getMovies());
    cout << "Merged BSTs: " << endl;
    resultEmpty->print();    // boş bastırmıyor??
    cout << "\n ************************\n";
    
    vector<User*> inter;
    c.findStartingWith("a",inter);
    cout<<"\n ************************\n" <<inter.size()<< endl;
    for(int i=0;i<inter.size();i++){
        cout<<"\n *******movies of " << inter[i]->getUsername() << endl ;
        inter[i]->printMovies();
    }
    c.print();

    Trie<User> tr;
    tr.insert("user1");
    tr.insert("abcdef123");
    tr.insert("12345ac");
    tr.insert("1345ac");

    vector<User*> v;
    c.wildcardSearch("alper??", v);

    
    cout<<"\n ************************\n";
    cout<<"\n wildcard Done\n"<< endl;
    for(int i=0;i<v.size();i++){
        cout<<"\n ***************" << i << " " << v[i]->getUsername() <<"***************"<< endl;
    }

    /*cout<<"\n *********find************\n";

    
    ////////////////////////////////////////////////////////////////////////////////////////////
    BST<Movie> emptyBST1, emptyBST2;
    BST<Movie> *resultEmpty = emptyBST1.merge(&emptyBST2);
    cout << "Merged Empty BSTs: ";
    resultEmpty->print();    // boş bastırmıyor??
    cout << "\n ************************\n";

    // Test case 2: Merge one empty BST with a non-empty BST
    BST<Movie> emptyBST, nonEmptyBST;
    nonEmptyBST.insert("testKey", Movie("testMovie", 42, 123));
    BST<Movie> *resultNonEmpty = emptyBST.merge(&nonEmptyBST);
    cout << "Merged Empty and Non-Empty BSTs: ";
    resultNonEmpty->print();
    cout << "\n ************************\n";

    // Test case 3: Merge two non-empty BSTs
    BST<Movie> bst1, bst2;
    bst1.insert("key8", Movie("movie8", 1, 1));
    bst1.insert("key2", Movie("movie2", 2, 2));
    bst1.insert("key3", Movie("movie3", 3, 3));
    bst2.insert("key4", Movie("movie4", 4, 4));
    bst2.insert("key10", Movie("movie10", 5, 5));
    bst2.insert("key6", Movie("movie6", 6, 6));
    cout<< bst2.search("key7") <<"\n" ;
    bst2.print();
    //bst1.printvector();
    cout << "\n ************************\n";
    BST<Movie> *resultMerged = bst1.merge(&bst2);
    cout << "Merged BSTs: \n" ;
    resultMerged->print();

    BST<Movie> *resultinter = bst1.intersection(&bst2);
    cout << "Intersection BSTs: \n" ;
    resultinter->print();*/

    
}