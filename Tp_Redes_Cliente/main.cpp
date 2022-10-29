#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <ctime>

using namespace std;


class Client{
public:
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    char buffer[1024]=" ";
    bool regresar=false;

    Client(int puerto){
       cout<<"Conectando al servidor..."<<endl<<endl;

        WSAStartup(MAKEWORD(2,0), &WSAData);
        server = socket(AF_INET, SOCK_STREAM, 0);
        addr.sin_addr.s_addr = inet_addr("192.168.1.106 ");
        addr.sin_family = AF_INET;
        addr.sin_port = htons(puerto);
        connect(server, (SOCKADDR *)&addr, sizeof(addr));
        cout << "Conectado al Servidor!" << endl;
        cout << "=====¡Bienvenido Al Sistema!====="<< endl;
    }

    void Enviar(){
        char aux[7]="volver";
        cout<<"Escribe el mensaje a enviar: ";
        fflush(stdin);
        gets(this->buffer);
        send(server, buffer, sizeof(buffer), 0);
        if(strcmp(buffer,aux)==0){
            regresar=true;
        }
        cout << "Mensaje enviado!" << endl;

    }


    void incativo(){
    send(server,"volver", sizeof(buffer), 0);
    }

    void Recibir(){
    recv(server, buffer, sizeof(buffer), 0);
    cout << "El servidor dice: " << buffer << endl;
    }

    void Punto2(){
    char aux[1024]=" ";
    int i=0;
        for(i=0;i<strlen(aux);i++){
            if(aux[i] == ' ')//esta vacio
                {
                recv(server, aux, sizeof(aux), 0);
                cout<< aux << endl;
                i=0;//lo uso para que el bucle sea"infinito " hasta que traiga todo la actividad
            }
        }

    }

     void enviarAutomaticamente (int opcion){
        if(opcion==0){
            send(server, "0", sizeof(buffer), 0);
        }

        if(opcion==1){
            send(server, "1", sizeof(buffer), 0);
        }
        if(opcion==2){
            send(server, "2", sizeof(buffer), 0);

        }
        if(opcion==4){
            send(server, "4", sizeof(buffer), 0);

        }
     }

     void CerrarSocket(){
       closesocket(server);
       WSACleanup();
       cout << "Socket cerrado." << endl << endl;
    }


};

int main()
{

    int opcion=0;
    int puerto=0;
    cout<<"Por favor ingrese el numero de puerto:"<<endl;
    cin>>puerto;
    Client *Cliente = new Client(puerto);

    clock_t t;
    t=clock();
    t=clock()-t;
    while(t/CLOCKS_PER_SEC<=120){
        cout << "----------BIENVENIDO AL MENU----------" <<endl << endl;
        cout << "1-Calcular" <<endl;
        cout << "2-Ver Registros De Actividades" <<endl;
        cout << "0-Cerrar Sesion" <<endl;

        cout << "Digite su opcion" <<endl;
        cin >> opcion;

        switch(opcion){
        case 1:
            Cliente->enviarAutomaticamente(opcion);
            Cliente->Recibir();
        break;
        case 2:
                Cliente->enviarAutomaticamente(opcion);
                cout<<"El registro es:"<<endl;
                Cliente->Punto2();
                break;
            case 0:
                Cliente->enviarAutomaticamente(opcion);
                cout<< "Usted se desconecto.Hasta la proxima."<< endl;break;
            default:
                cout << "Error, esa opcion no existe"<< endl;
        }

    }//WHILE

    if(t/CLOCKS_PER_SEC>=120){

        cout<<"---- Desconectado por inactividad. Superaste los 2 minutos. ----"<<endl;
        Cliente->enviarAutomaticamente(4);//le mando la opcion 4
        return 0;
    }

}
