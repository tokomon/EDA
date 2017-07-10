
#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <thread>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <mutex>

using namespace std;

mutex io_mutex;

class c_File
{
public:
    fstream file;
    string namefile;
    string contenido;

    string getNamefile() {
        return namefile;
    }

    c_File(string name){
           namefile = name;
           createFile(name);
       }

       void createFile(string namefile){
           file.open(namefile,std::fstream::in | std::fstream::out | std::fstream::app);
           file<<"hello world!" << endl;
           file.close();

/*
           cout << "Ingresa el contenido del archivo: ";
           getline(cin, contenido);

           ofstream fs(namefile.c_str());
           fs << contenido << endl;
           fs.close();
           cout << "El archivo ha sido creado correctamente" << endl;
           system("pause");*/

       }
       bool leer()
       {
          /* cout << "Ingresa el nombre del archivo que quieres leer(sin el .txt): ";
           cin.ignore();
           getline(cin, contenido2);
           contenido2 += ".txt";*/
           ifstream fs(namefile.c_str(), ios:: in );
           char linea[128];
           long contador = 0L;
           if (fs.fail())
             cerr << "El fichero no existe" << endl;
           else
             while (!fs.eof()) {
               fs.getline(linea, sizeof(linea));
               cout << linea << endl;
               if ((++contador % 24) == 0) {
                 cout << "continuar...";
                 cin.get();
               }
             }
           fs.close();
           system("pause");
           return true;
       }

       void modificar()
       {
           cout << "Ingresa el NUEVO contenido del archivo: ";
           getline(cin, contenido);
           ofstream fs(namefile.c_str(), ios::out);
           fs << contenido << endl;
           fs.close();
           cout << "El archivo ha sido modificado correctamente" << endl;
           system("pause");
       }

   /*
       void merge(string text){
           file.open(namefile,std::fstream::in | std::fstream::out | std::fstream::app);
           file<< text <<endl;
           file.close();
       }*/



};



template <class G>
class Fx_Disper
{
public:
    typedef typename G::N T;
///metodo de compresion, ascii

    vector<int> binario(int num)
  {
      vector<int>binarios;
      int base=2;
          while(num>=2)
          {
              binarios.insert(binarios.begin(),num%base);
              num=num>>1;
          }
          binarios.insert(binarios.begin(),num);

          return binarios;
  }

    int convert_to_decimal(vector<int> numero)///GENERA EL ALEATORIO EN DECIMAL
    {
        int num_decimal;
        long base=2;
        num_decimal=0;
        long tam=numero.size()-1;
        long i;
        for( i=0; i<=tam;i++)
        {
            if(numero[i]==1)
            {
                num_decimal+=pow(base,tam-i);
            }
        }

        //si es multiplo de 5 lo paso
        if(num_decimal%5==0)
        {
            num_decimal=num_decimal+2;
        }
        return num_decimal;
    }


    int operator()(T num)
    {
        int aux=0;
        vector<vector<int> > contenedor;
        for(int i=0;i<num.size();i++)
        {
            aux=num[i];//caracter ascii
          //  cout<<"numero: "<<aux<<endl;
            contenedor.push_back(binario(aux));
            while(contenedor[i].size()<8)
            {
                contenedor[i].insert(contenedor[i].begin(),0);
            }
         //   cout<<num.size()<<endl;
        }





        //hacer el xor de
        int resultado=0;
        vector<int> adecimal;


            for(int u=0;u<contenedor[0].size();u++)
            {
                resultado=0;
                for(int w=0;w<contenedor.size();w++)
                {
                   // cout<<"DE: "<<w<<" palabra "<<u<<" posicion "<<contenedor[w][u]<<endl;
                    resultado= resultado ^(contenedor[w][u]);

                }
               // cout<<resultado;
                adecimal.push_back(resultado);
            }



        aux=convert_to_decimal(adecimal);
   //     cout<<aux<<endl;

      //  cout<<"este es aux: "<<aux<<endl;

        return aux;

     }

};


template <class G>
class ListAdtor
{
public:
    typedef typename G::N N;
    typedef typename G::Node Node;


   vector<Node*> l;
   int cont;

   Node* find(N x)
   {
   	cont=0;
        for(int i=0; i<l.size();i++)
        {
        	
            if(l[i]->m_data == x) return l[i];
            cont++;
        }
        return nullptr;
    }

   bool insert(Node* x)
   {

     //  if(find(x)) return 0;
       l.push_back(x);
       return 1;
   }
   bool remove(N x)
   {
       if(!find(x))return 0;
      // l.remove(x);
       typename vector<Node*> ::iterator it = l.begin();
		l.erase(it+cont);
       return 1;
   }

   void imprimir()
   {
       for(int i=0; i<l.size();i++)
       {
           cout<<l[i].m_data<<" "<<endl;
       }
   }
};



template<class G>
class c_HashTable
{
public:
    typedef typename G::N N;
    typedef typename G::Node Node;
    typedef typename G::List List;
    typedef typename G::Fx Fx;


    List *m_ht;
    Fx m_f;
    int m_size;
    vector<Node*> m;
    c_HashTable()
    {
         m_ht=new List[m_size]();
        // cout<<"n "<<m_size<<endl;


    }

    c_HashTable(int size)
    {

         m_ht=new List[size];
    //     cout<<"n "<<size<<endl;

    //    cout<<"nohpi"<<endl;
      //  m_ht[0].l.push_back("s");
     //   cout<<"hola "<<m_ht[0].l.size()<<endl;

        m_size=size;
      /*  for(int i=0; i<m_size;i++)
        {
            cout<<"nohpi"<<endl;

         // m[i]=nullptr;
        }
*/
    }

    bool _insert(Node* x)
    {
      //  int id=m_f(x->m_data+x->str)%m_size;
         int id=m_f(x->m_data)%m_size;
  /*       id+=m_f(x->str )%m_size;
         id+=m_f(x->user )%m_size;

*/


        return m_ht[id].insert(x);
    }

    bool remove(N x)
    {
        int id=m_f(x)%m_size;
        return m_ht[id].remove(x);
    }

    Node* find(N x)
    {
        int id=m_f(x)%m_size;
   /*     int id=m_f(x->m_data)%m_size;
        id+=m_f(x->str )%m_size;
         id+=m_f(x->user )%m_size;
*/
        if (!m_ht[id].find(x)) return nullptr;
       // cout<< m_ht[id].find(x)->m_data<<endl;
        return m_ht[id].find(x);
    }

    void imprimir()
    {cout<<"Imprimir ht"<<endl;
        for(int i=0; i<m_size;i++){

            for(int j=0; j<m_ht[i].l.size();j++)
            {
                cout<< i<<" "<<j<<" "<<m_ht[i].l[j]->m_data<<" "<<endl;
            }
        }
        return ;
    }


};


//todo se haa en n msmo achvo
//qe esta en el msmo Grafo
template<class G>
class c_Node
{
public:
  typedef typename G::N N;
  typedef typename G::Edge Edge;
  c_Node(N x, c_File* _file)
  {
    m_data=x;//nombre del archivo
   
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
    str = oss.str();
 //   cout << str << endl;
     file=_file;
     estado=true;
   
  }

  void set_branch(string b)
  {
  	 branch=b;
  }
   void set_user(string b)
  {
  	 user=b;
  }

  N m_data;//
  c_File* file;
   
  ostringstream oss;
  string str;
  bool estado;
  string user;

  string branch;
  vector<Edge*> m_edges;//guardar aristas que solo salen

};



template<class G>
class c_Edge
{
public:
  typedef typename G::E E;
  typedef typename G::Node Node;
  c_Edge(E x,Node* a,Node* b){
    m_data=x;
    m_node[0]=a;
    m_node[1]=b;
  }


  E m_data;
  Node* m_node[2];//0 es entran y 1 salen
  //0 ->origen
};

template<class G>
class c_Branch
{
public:
	
 	typedef typename G::Node Node;
	string name;
	Node* origen;//de donde sale
	Node* fin;//el nodo actal de esa branch
	c_Branch (string n,Node* o,Node* f)	{
		 name=n;
		 origen=o;
		 fin=f;
	}

	void set_f(Node* f)
	{
		fin=f;
	}
};

struct G
{
    typedef G Self;
    typedef  c_Node<Self> Node;
    typedef  c_Edge<Self> Edge;
    typedef  c_Branch<Self> Branch;


        ///Para la tabla Hash

    typedef  ListAdtor<Self> List;
    typedef  Fx_Disper<Self> Fx;

};




template<class n,class e>
class Grafo
{
public:
  typedef  Grafo<n,e> Self;
  typedef  c_Node<Self> Node;
  typedef  c_Edge<Self> Edge;
  typedef  c_HashTable<Self> Hash;
  typedef  ListAdtor<Self> List;
  typedef  Fx_Disper<Self> Fx;
  typedef  c_Branch<Self> Branch;

  typedef  n N;
  typedef  e E;


  Hash *ht;
  vector<Branch*> m_branch;//guardar el primer y ultimo estado y el nombre del branch
  string owner;
  Node* head;


   vector<Node*> m_nodes;
   vector<Edge*> m_gedges;
   int g_size;
   Node* current_node;
   Branch* current_branch;
   int cont;
   int cont_b;
   c_File* file;



   Grafo(int size,string user,c_File* _file)
   {
     g_size=size;
     owner = user;

     ht=new Hash(size);
     current_node = nullptr;
     cont=0;
     cont_b=0;
     file=_file;
     head=nullptr;
     Branch* b=new Branch("master",head,current_node);

     m_branch.push_back(b);
     current_branch=m_branch[0];
     
   }

   void cambiar_user(string new_user )
   {
       owner=new_user;
   }
   //añadir una branch en el estado n_branch
   void add_branch(string branch,N n_branch)//como se llamara y en que estado
   {
   	//solo bsca s exste en nodo para crear na branch
       Node* p =ht->find(n_branch);
       cout<<n_branch<<endl;
       if (!p) return;//si no hay branch
       m_branch.push_back(new Branch(branch,p,p));//el currnt sera el nodo de donde sacamos la branch
   }
   //primero se tene que volver  a la branch para pode nseta

   //volver a la branch que quieras
   void cambiar_branch(string branch)
   {
       for(int i=0; i<m_branch.size();i++)
       {
           if ((m_branch[i])->name ==branch)
           {
               current_node = (m_branch[i])->fin;
               current_branch=m_branch[i];
               cont_b=i;
           }
       }
       return;
   }


//se va a insertar el nombre del file
   bool insert_node(N x,c_File* file)
   {

       io_mutex.lock();
     Node* temp=new Node(x,file);
     temp->set_branch(current_branch->name);
     temp->set_user(owner);


     m_nodes.push_back(temp);
   //  cout<<"entra"<<endl;
    ht->_insert(temp);
    if (current_node)
    {
        insert_edge(cont,current_node->m_data,temp->m_data);
    }//else{ m_branch.push_back(make_tuple(current_branch,current_node,current_node));}

    current_node = temp;

   	(m_branch[cont_b])->set_f(current_node);
   cont++;



    io_mutex.unlock();
     return 1;


   }
//hacer que la arista se haga automaticamente

   bool insert_edge(E x,N a,N b)
   {
     Node *Na,*Nb;
     for(int i =0; i<m_nodes.size();i++)
       {

         if(m_nodes[i]->m_data ==a)Na=m_nodes[i];
         if(m_nodes[i]->m_data ==b)Nb=m_nodes[i];

       }

     Edge* temp= new Edge(x,Na,Nb);
     Na->m_edges.push_back(temp);
  //   Nb->m_edges.push_back(temp);
     m_gedges.push_back(temp);

     return 1;
   }

   bool erase_edge(E x,N a, N b)
   {
     Node *Na,*Nb;
     for(int i=0;i<m_nodes.size();i++)
       {
         if(m_nodes[i]->m_data==a)Na=m_nodes[i];
         if(m_nodes[i]->m_data==b)Nb=m_nodes[i];
       }
       /*
     Edge* borrar;//borrar las conexiones de las aristas con los demas nodos
     for(int i=0;i<m_nodes.size();i++)
       {
         for(int j=0;j<m_nodes[i]->m_edges.size();j++)
           {
             if(m_nodes[i]->m_edges[j]->m_data==x && m_nodes[i]->m_edges[j]->m_node[0]==Na && m_nodes[i]->m_edges[j]->m_node[1]==Nb )
               {
                 m_nodes[i]->m_edges.erase(m_nodes[i]->m_edges.begin()+j);
               }
           }
       }*/
     for(int i=0;i<m_gedges.size();i++)
       {
         if(m_gedges[i]->m_data==x && m_gedges[i]->m_node[0]==Na && m_gedges[1]->m_node[1]==Nb)
           {/*
             borrar=m_gedges[i];
             m_gedges.erase(m_gedges.begin()+i);
             delete borrar;*/
           }
       }
     return 1;

   }

   bool erase_node(N x)
   {
   	 Node* p =ht->find(x);
     //  cout<<n_branch<<endl;
       if (!p) return false;//si no se enconto el nodo a borrar
       p->estado=false;
    //   ht->remove(x);//borrar la cola
       return true;
   /*
     Node* borrar;
     for(int i=0;i<m_nodes.size();i++)
       {
         if(m_nodes[i]->m_data==x)
           {
             borrar=m_nodes[i];
             for(int j=0;j<m_nodes[i]->m_edges.size();j++)
               {
                 erase_edge(m_nodes[i]->m_edges[j]->m_data,m_nodes[i]->m_edges[j]->m_node[0]->m_data,m_nodes[i]->m_edges[j]->m_node[1]->m_data);
               }
             m_nodes.erase(m_nodes.begin()+i);
             delete borrar;
           }
       }*/
     return 1;

   }
   bool restore(N x)
   {

   }
   E conexion_nodos(N a,N b)
     {
       for(int x=0;x<m_gedges.size();x++)
         {

           if(m_gedges[x]->m_node[0]->m_data==a && m_gedges[x]->m_node[1]->m_data==b)
             {
               return m_gedges[x]->m_data;
             }

         }

       return 0;

     }

   void imprimir()
   {
       cout<<"Branch"<<endl;

       for(int i=0;i<m_branch.size();i++)
         {
           cout<<(m_branch[i])->name<<endl;
         }
       cout<<endl;

	fstream grafito;
    grafito.open("grafito.dot",fstream::out | fstream::binary);
    if (not grafito.is_open()) return; ///no se pudo abrir el archivo, por alguna razon
    grafito << "# Printing printPersistence" << endl;
    grafito << "digraph G{ " << endl;
  //  grafito <<     "node [shape=circle];"<< endl;




     cout<<"Nodos"<<endl;
     for(int i=0;i<m_nodes.size() &&  m_nodes[i]->estado ;i++)
       {
       //  m_nodes[i]->point.setX(30);

         cout<<m_nodes[i]->m_data<<endl;
         grafito<<m_nodes[i]->m_data<<endl;
       }
     cout<<endl;


     cout<<"Aristas"<<endl;
     for(int i=0;i<m_gedges.size() && m_gedges[i]->m_node[1]->estado;i++)
       {
         cout<<m_gedges[i]->m_data<<endl;
       }


    cout<<endl;

    cout<<"conexiones"<<endl;
    

    for(int i =0;i<m_gedges.size() &&  m_gedges[i]->m_node[1]->estado ;i++)
      {
       /* m_gedges[i]->m_node[0]->point.setX(x);
        m_gedges[i]->m_node[1]->point.setX(x+100);
        QLine linea(m_gedges[i]->m_node[0]->point,m_gedges[i]->m_node[1]->point);
       painter->drawLine(linea);

       painter->drawText(m_gedges[i]->m_node[0]->point,m_gedges[i]->m_node[0]->data);
       painter->drawText(m_gedges[i]->m_node[1]->point,m_gedges[i]->m_node[1]->data);

       painter->drawEllipse(m_gedges[i]->m_node[0]->point,15,15);
       painter->drawEllipse(m_gedges[i]->m_node[1]->point,15,15);
        */
       cout<<m_gedges[i]->m_data<<" De "<<m_gedges[i]->m_node[0]->m_data<<" a "<<m_gedges[i]->m_node[1]->m_data<<endl;
        //x+=100;
      }





int  i=0;
       

    for( i =0; i<m_gedges.size() &&  m_gedges[i]->m_node[1]->estado ;i++)
      {
        grafito <<m_gedges[i]->m_node[0]->m_data<<" -> "<<m_gedges[i]->m_node[1]->m_data<<endl;
      }
    grafito << "}" << endl;
    grafito.close();

system(("dot -Tpng grafito.dot -o "+to_string(i)+".png").c_str());

   }







   Grafo clonar_grafo()
   {
     Grafo m_graf(m_nodes.size(),owner,file);
     for(int i=0;i<m_nodes.size();i++)
       {
         m_graf.insert_node(m_nodes[i]->m_data,m_nodes[i]->file);
       }

         for(int i=0;i<m_nodes.size();i++)
           {
             for(int j=i+2;j<m_nodes.size();j++)
               {
                 int v=conexion_nodos(m_graf.m_nodes[i]->m_data,m_graf.m_nodes[j]->m_data);

                  if(v!=0)
                  {
                   m_graf.insert_edge(v,m_graf.m_nodes[i]->m_data,m_graf.m_nodes[j]->m_data);
                  }


               }
             cout<<endl;


               }


       for(int i=0;i<m_branch.size();i++)
         {
         //	 m_graf.add_branch((m_branch[i])->name,(m_branch[i])->origen->m_data);
       //    cout<<(m_branch[i])->name<<endl;
         }
       cout<<endl;

/*

    for(int i =0;i<m_gedges.size() &&  m_gedges[i]->m_node[1]->estado ;i++)
      {
        m_graf.insert_edge(m_gedges[i]->m_data,m_gedges[i]->m_node[0]->m_data,m_gedges[i]->m_node[1]->m_data);

//       cout<<m_gedges[i]->m_data<<" De "<<m_gedges[i]->m_node[0]->m_data<<" a "<<m_gedges[i]->m_node[1]->m_data<<endl;
        //x+=100;
      }*/
           return m_graf;

         }




};





template<class N,class E>
class c_Persistence
{
public:
    vector<Grafo<N,E>>heads;
    c_File* file;
    int _size;
    string _user;
    int num_estado;
    c_Persistence(int size,string user,c_File* _file)
    {
        cout<<"Se ha creado un repositorio"<<endl;
        file=_file;
        _size=size;
        _user=user;
        num_estado=0;
    }

    bool insert_node(N x,c_File* file)
    {


        if (heads.size()==0)
        {
            Grafo<N,E> grafito(_size,_user,file);
            grafito.insert_node(x,file);
            heads.push_back(grafito);


        }
        else
        {

            Grafo<N,E> grafo_ant=heads[heads.size()-1].clonar_grafo();

            grafo_ant.insert_node(x,file);
       //     cout<<"-----------"<<endl;
        //    heads[0].ht->imprimir();


            heads.push_back(grafo_ant);

        //     heads[1].ht->imprimir();

        }

        num_estado++;
    }


    bool erase_node(N x)
    {
      for(int i=0;i<heads[num_estado].m_nodes.size();i++)
        {
          if(heads[num_estado].m_nodes[i]->m_data==x)
            {

              for(int j=0;j<heads[num_estado].m_nodes[i]->m_edges.size();j++)
                {
                  heads[num_estado].erase_edge(heads[num_estado].m_nodes[i]->m_edges[j]->m_data,heads[num_estado].m_nodes[i]->m_edges[j]->m_node[0]->m_data,heads[num_estado].m_nodes[i]->m_edges[j]->m_node[1]->m_data);
                }
              heads[num_estado].m_nodes.erase(heads[num_estado].m_nodes.begin()+i);

            }
        }
      return 1;
    }



   //añadir una branch en el estado n_branch
   void add_branch(string branch,N n_branch)//como se llamara y en que estado
   {
   	cout<<"ñoseee"<<endl;
   	  heads[heads.size()-1].add_branch(branch,n_branch);
   }
   //primero se tene que volver  a la branch para pode nseta

   //volver a la branch que quieras
   void cambiar_branch(string branch)
   {
       heads[heads.size()-1].cambiar_branch(branch);
   }


   void imprimir()
   {  
   	for(int i=0;i<heads.size();i++)
        {
        	heads[i].imprimir();
        }
    }



};







int main(int argc, char const *argv[])
{
  

    string user[]={"user1", "user2", "user3","user4"};
    int nt = thread::hardware_concurrency();
    c_File* file= new c_File("muu");
//    vector<thread> th(nt);


    //el file lo tendra el grafo y cada vez que se inserte un estado
    //se supone que el ya modifico antes el file que se encuentra en el grafo


    c_Persistence<string,int> cversion(10,"user",file);

/*
    string contenido;
    string contenido2;
    int opcion;
*/

     cversion.insert_node("A",file);

     cversion.insert_node("B",file);
    cversion.insert_node("C",file);


    cversion.add_branch("new","B");
    cversion.cambiar_branch("new");
     cversion.insert_node("D",file);

    cversion.insert_node("E",file);
     cversion.imprimir();


/*

    ////hacer path copy :3
    ///
   Grafo<string,int> grafito(10,"_user",file);

    grafito.insert_node("A",file);

   grafito.insert_node("B",file);
    grafito.insert_node("C",file);
    grafito.add_branch("new","B");
    grafito.cambiar_branch("new");
    grafito.insert_node("D",file);
    grafito.insert_node("E",file);
    grafito.insert_node("G",file);
    grafito.cambiar_branch("master");
    grafito.insert_node("F",file);

*/
    ///mostrando
 /*   cversion.heads[3].ht->imprimir();
    cout<<endl;

    cversion.heads[3].imprimir();*/
/*

    grafito.ht->imprimir();
        cout<<endl;

        grafito.imprimir();

    grafito.erase_node("E");

    grafito.ht->imprimir();
        cout<<endl;

        grafito.imprimir();


*/
    //for(int i = 0; i < sizeof(user) ; i++)
    //un nodo es un commit, se debe guardar con el usuario y la fecha



/*
    ///paralelismo
    for (int i =0; i< nt ; i++)
    {
        th[i]=  thread (&Grafo<string,int>::insert_node,&grafito,user[i]);
    }

    for (int i =0; i< nt ; i++)
    {
        th[i].join();
    }
*/



  // cout<<(grafito.ht->find("A"))->m_data<<endl;










         //   A.Print(A.m_head,&p);



}
