/***************************************************************************************

    CarGL (Objects.h)

    Grado en Ingenier�a Multimedia.
    Pr�ctica de Gr�ficos por Computador.
    OpenGL con Shaders.
  --------------------------------------------------------------------------------------

    2012 - 2022 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)

****************************************************************************************/

//---------------------------------------------------------------------------
#ifndef ObjectsH
#define ObjectsH
//---------------------------------------------------------------------------

#define GLEW_STATIC

#include "Shader.h"
#include "Program.h"

#include <GL/glui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Identificadores internos de los objetos y el coche
#define CARRETERA_ID 10
#define EDIFICIO_ID 20

#define COCHE_ID 500
#define SEMAFORO_ID 30
#define BANCO_ID 40
#define FAROLA_ID 50
#define CONTENEDOR_ID 60
#define BUZON_ID 70
#define FUENTE_ID 80
#define STOP_ID 90
#define MARCADOR_ID 900
#define MODO_CAMARA_ID 601
// IDs para los callbacks de TGui
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT2_ENABLED_ID    202
#define LIGHT0_POSITION_ID   210
#define LIGHT1_POSITION_ID   211
#define LIGHT2_POSITION_ID   212
#define LIGHT0_INTENSITY_ID  220
#define LIGHT1_INTENSITY_ID  221
#define LIGHT2_INTENSITY_ID 222

#define ENABLE_ID            300
#define DISABLE_ID           301

#define RESET_ID             400

#define SEL_ID               500

// Datos del formato 3DS (x, y, z, A, B, C, u, v)
#define POSITION_COMPONENT_COUNT    3
#define NORMAL_COMPONENT_COUNT      3
#define UV_COMPONENT_COUNT          2
// C�lculo del stride (3+3+2)*4 = 8*4 = 32
#define STRIDE                      32

// Nombre de los attributes
#define A_POSITION  "a_Position"
#define A_NORMAL    "a_Normal"

// Nombre de los uniforms
#define U_PROJECTIONMATRIX      "u_ProjectionMatrix"
#define U_MVMATRIX              "u_MVMatrix"
#define U_VMATRIX               "u_VMatrix"
#define U_COLOR                 "u_Color"
#define U_LUZ0                  "u_Luz0"
#define U_LUZ1 "u_Luz1"
#define U_LUZ2 "u_Luz2"

#define U_AMBIENT "u_Ambient"

#define MODO_VISTA 90010
#define PROYECCION_ID 602
//************************************************************** Clase TPrimtiva

class TPrimitiva
{
public: // Atributos de la clase
		int ID;				    // DisplayLists del objeto
		int tipo;               // Tipo de Objeto
		float tx,ty,tz; 	    // Posici�n del objeto
		float sx,sy,sz; 	    // Escalado del objeto
		float rx,ry,rz;
		float rry;
		// Rotaci�n del objeto
		float rr,gr,gc;               // Rotaci�n de las ruedas

        float marcadorOffsetX;
        float marcadorOffsetY;
        float marcadorOffsetZ;

		float colores[2][4];    // Color RGB y canal Alfa

		float   *modelo0;        // modelo a representar
		int     num_vertices0;   // n�mero de v�rtices

        float   *modelo1;        // modelo a representar
		int     num_vertices1;   // n�mero de v�rtices

        float steeringAngle;

public: // M�todos
 		TPrimitiva(int DL, int tipo);
        void __fastcall Render(int seleccion, bool reflejo=false);
          void InitVariables();
          void Reset();
};

//************************************************************** Clase TEscena

class TEscena
{
public: // Atributos de la clase
        int wireframe;
		int   	seleccion;   	// Objeto seleccionado, 0=ninguno
        int		num_objects;    // N�mero de objetos (excepto coches)
        int     num_cars;       // N�mero de coches
        int sentido;
        TPrimitiva  *cars[10];
        TPrimitiva  *objects[100];

        // Handles de los attributes y uniforms
        int aPositionLocation;
        int aNormalLocation;
        int uProjectionMatrixLocation;
        int uMVMatrixLocation;
		int uVMatrixLocation;
		int uColorLocation;
		int uLuz0Location;
		int uLuz1Location;
        int uLuz2Location;

        int uAmbient;

        int uPositionLuz0Location;
        int uPositionLuz1Location;
        int uPositionLuz2Location;

        int uIntensidadLuz0Location;
        int uIntensidadLuz1Location;
        int uIntensidadLuz2Location;


    float scaleZ = 0;
    float rotationX = 0.0f;
       float rotationY = 0.0f;
       float rotationZ = 0.0f;
       float zoom = 40.0f; // Zoom inicial
       float translationX = 0.0f;
        float translationY = 0.0f;
         float translationZ = 0.0f;
        int lastMouseX = 0;
       int lastMouseY = 0;
       int mouseButton = -1;


		glm::mat4 projectionMatrix; // Almacena la matriz de proyecci�n
        glm::mat4 viewMatrix;       // Almacena la matriz de la vista (c�mara)

		Program  *shaderProgram;    // Almacena el programa de OpenGL (ShaderProgram)

        // Vectores de luces y materiales
        GLfloat light0_ambient[4];
        GLfloat light0_diffuse[4];
        GLfloat light0_specular[4];
        GLfloat light0_position[4];

        GLfloat light1_ambient[4];
        GLfloat light1_diffuse[4];
        GLfloat light1_specular[4];
        GLfloat light1_position[4];

        GLfloat light2_ambient[4];
        GLfloat light2_diffuse[4];
        GLfloat light2_specular[4];
        GLfloat light2_position[4];

        GLfloat mat_ambient[4];
        GLfloat mat_diffuse[4];
        GLfloat mat_specular[4];
        GLfloat mat_shininess[1];

        float   xy_aspect;
        int     last_x, last_y;

        // live variables usadas por GLUI en TGui

        int     z_buffer;
        int     culling;
        int proyeccion;

        int     show_car;
        int     show_wheels;
        int     show_road;

        GLfloat view_position[3];
        GLfloat view_rotate[16];
        float   scale;
       
float carAngle;             // �ngulo de rotaci�n del coche
 

// En TEscena (Objects.h)
int camara;             // Control de la c�mara activa
glm::vec3 followCameraOffset; // Offset para la c�mara de seguimiento




public: // M�todos
		TEscena();

        void __fastcall InitGL();
		void __fastcall Render();

		void __fastcall RenderCars(bool reflejo);
		void __fastcall RenderObjects(bool reflejo);

		void __fastcall AddCar(TPrimitiva *car);
		void __fastcall AddObject(TPrimitiva *object);
        void __fastcall CrearEscenario();

		TPrimitiva __fastcall *GetCar(int id);

		void __fastcall Pick3D(int mouse_x, int mouse_y);

        
        void InitVariables(); // Funci�n para inicializar las variables


};

//************************************************************** Clase TGui

class TGui
{
public:
    int globalModifiers; // Estado global de teclas modificadoras

        int a_Proyeccion;
        int aVista;
        int             window_id;
        int aCamara;
        // live variables usadas por GLUI
        int             sel;
        int             enable_panel2;
        int             light0_enabled;
        int             light1_enabled;
        int light2_enabled;

        int ambient_enabled;

        float light0_intensity;
        float light1_intensity;
        float light2_intensity;
        float light0_position[4];
        float light1_position[4];
        float light2_position[4];

int lastMouseX;  // Última posición X del ratón
int lastMouseY;  // Última posición Y del ratón
int mouseButton; // Botón del ratón presionado (-1: ninguno)
       

        GLUI            *glui, *glui2;
        GLUI_Spinner    *light0_spinner;
        GLUI_Spinner    *light1_spinner;
        GLUI_Spinner *light2_spinner;
        GLUI_RadioGroup *radio;
        GLUI_Panel      *obj_panel;
        GLUI_Rotation   *view_rot;

public:
        TGui();
        void __fastcall Init(int main_window);
        void __fastcall ControlCallback(int control);
        void __fastcall Idle( void );
        void __fastcall Reshape( int x, int y  );
        void __fastcall Motion( int x, int y  );
        void __fastcall Mouse(int button, int button_state, int x, int y );
};

//************************************************************** Variables de clase

extern TEscena  escena;
extern TGui     gui;

#endif
