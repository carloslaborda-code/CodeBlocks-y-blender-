/****************************************************************************************

    CarGL (Objects.cpp)

    Grado en Ingenier�a Multimedia.
    Pr�ctica de Gr�ficos por Computador.
    OpenGL con Shaders.
  ---------------------------------------------------------------------------------------

    2012 - 2022 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)


*****************************************************************************************/

#include "Objects.h"
#include <GL/glui.h>

#include "load3ds.c"

// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light0_position_c[4] = {-100.0f, 100.0f, 50.0f, 1.0f };

GLfloat light1_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light1_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat light2_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light2_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light2_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light2_position_c[4] = {   0.0f, 100.0f,  50.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess_c[1] = { 100.0f };

// Matriz de 4x4 = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -2.0, -9.0 };

float coloresc_c[2][4] = { {0.8, 0.5, 0.0, 1.0}, {0.5, 0.5, 0.5, 1.0}}; // Color del coche
float coloresr_c[2][4] = { {0.3, 0.3, 0.3, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de la carretera

//************************************************************** Variables de clase

TEscena escena;
TGui    gui;

//************************************************************** Clase TPrimitiva

TPrimitiva::TPrimitiva(int DL, int t)
{

    ID   = DL;
    tipo = t;
    marcadorOffsetX = 0.0f;
    marcadorOffsetY = -0.50f;
    marcadorOffsetZ = 7.0f;
    sx = sy = sz = 1;
    rx = ry = rz = 0;
	switch (tipo) {
		case CARRETERA_ID: {  // Creaci�n de la carretera
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS((char*)"../../Modelos/carretera.3ds", &num_vertices0);


            break;
		}
		case EDIFICIO_ID: {  // Creaci�n de la carretera
		   tz = ty = 0;
            tx = -23;


            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS((char*)"../../Modelos/Edificio.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
		case COCHE_ID: { // Creaci�n del coche

		    tx = 7.5911;
		    ty =  0;
		    tz =  -66.035;
		    rr =  0.0;

		    memcpy(colores, coloresc_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS((char*)"../../Modelos/Auidi2.3ds", &num_vertices0);
            modelo1 = Load3DS((char*)"../../Modelos/rueda.3ds", &num_vertices1);
            break;


		}
		case SEMAFORO_ID: {  // Creaci�n del sem�foro
    tx = 0.0f;  // Posici�n inicial X
    ty = 0.0f;  // Posici�n inicial Y
    tz = 0.0f;  // Posici�n inicial Z
    ry = 0.0f;  // Sin rotaci�n inicial

    memcpy(colores, coloresr_c, 8 * sizeof(float));  // Color del sem�foro

    // Cargar el modelo del sem�foro
    modelo0 = Load3DS((char*)"../../Modelos/semaforo.3ds", &num_vertices0);
    modelo1 = NULL;  // No hay segunda parte para este modelo
    break;
}
    case BANCO_ID: {  // Creaci�n del banco
    tx = 0.0f;  // Posici�n inicial X
    ty = 0.0f;  // Posici�n inicial Y
    tz = 0.0f;  // Posici�n inicial Z
    ry = 0.0f;  // Sin rotaci�n inicial

    memcpy(colores, coloresr_c, 8 * sizeof(float));  // Color del banco

    // Cargar el modelo del banco
    modelo0 = Load3DS((char*)"../../Modelos/banco.3ds", &num_vertices0);
    modelo1 = NULL;  // No hay segunda parte para este modelo
    break;
}
    case FAROLA_ID: {  // Creaci�n de la farola
    tx = 0.0f;  // Posici�n inicial X
    ty = 0.0f;  // Posici�n inicial Y
    tz = 0.0f;  // Posici�n inicial Z
    ry = 0.0f;  // Sin rotaci�n inicial

    memcpy(colores, coloresr_c, 8 * sizeof(float));  // Color de la farola

    // Cargar el modelo de la farola
    modelo0 = Load3DS((char*)"../../Modelos/farola.3ds", &num_vertices0);
    modelo1 = NULL;
    break;
}
case CONTENEDOR_ID: {  // Creaci�n del contenedor
    tx = 0.0f;
    ty = 0.0f;
    tz = 0.0f;
    ry = 0.0f;

    memcpy(colores, coloresr_c, 8 * sizeof(float));  // Color del contenedor

    // Cargar el modelo del contenedor
    modelo0 = Load3DS((char*)"../../Modelos/contenedor.3ds", &num_vertices0);
    modelo1 = NULL;
    break;
}
case BUZON_ID: {  // Creaci�n del buz�n
    tx = 0.0f;
    ty = 0.0f;
    tz = 0.0f;
    ry = 0.0f;

    memcpy(colores, coloresr_c, 8 * sizeof(float));  // Color del buz�n

    // Cargar el modelo del buz�n
    modelo0 = Load3DS((char*)"../../Modelos/buzon.3ds", &num_vertices0);
    modelo1 = NULL;
    break;
}
    case FUENTE_ID: {  // Creaci�n de la fuente
    tx = 0.0f;  // Posici�n inicial X
    ty = 0.0f;  // Posici�n inicial Y
    tz = 0.0f;  // Posici�n inicial Z
    ry = 0.0f;  // Sin rotaci�n inicial

    memcpy(colores, coloresr_c, 8 * sizeof(float));  // Color de la fuente

    // Cargar el modelo de la fuente
    modelo0 = Load3DS((char*)"../../Modelos/fuente.3ds", &num_vertices0);
    modelo1 = NULL;  // No hay segunda parte para este modelo
    break;
}

case STOP_ID: {  // Creaci�n del stop
    tx = 0.0f;  // Posici�n inicial X
    ty = 0.0f;  // Posici�n inicial Y
    tz = 0.0f;  // Posici�n inicial Z
    ry = 0.0f;  // Sin rotaci�n inicial

    memcpy(colores, coloresr_c, 8 * sizeof(float));  // Color del stop

    // Cargar el modelo del stop
    modelo0 = Load3DS((char*)"../../Modelos/stop.3ds", &num_vertices0);
    modelo1 = NULL;  // No hay segunda parte para este modelo
    break;
}
case MARCADOR_ID: { // Creaci�n del marcador
    tx = 0.0f;  // Posici�n inicial X
    ty = 0.0f;  // Posici�n inicial Y
    tz = 0.0f;  // Posici�n inicial Z
    ry = 0.0f;  // Sin rotaci�n inicial

    memcpy(colores, coloresr_c, 8 * sizeof(float));  // Color del marcador

    // Cargar el modelo del marcador
    modelo0 = Load3DS((char*)"../../Modelos/marcador.3ds", &num_vertices0);
    modelo1 = NULL;  // No hay segunda parte para este modelo
    break;
}





	} // switch
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo)
{

    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;
    glStencilFunc(GL_ALWAYS, 0, 0xFF);

    switch (tipo) {

        case CARRETERA_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

                // Pintar las l�neas
                glUniform4fv(escena.uColorLocation, 1, colores[1]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);


            }
            break;
        } // case CARRETERA_ID:
        case EDIFICIO_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }

            break;
        } // case CARRETERA_ID:
       case COCHE_ID: {
           glStencilFunc(GL_ALWAYS,ID, 0xFF);


    if (escena.show_car) {


         // Renderizar el cuerpo del coche
        glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
        glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
        glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

        glm::mat4 modelMatrix = glm::mat4(1.0f);

        // Aplica la traslaci�n general del coche (posici�n)
        modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));

        // Aplica la rotaci�n general del coche en torno al eje Y seg�n el �ngulo del coche
        modelMatrix = glm::rotate(modelMatrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));

        // Calcula la matriz de modelo-vista
        glm::mat4 modelViewMatrix = escena.viewMatrix * modelMatrix;
        glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
    }

  if (escena.show_wheels) {
        float DesplazamientoX = 4.3; // Izquierda y derecha
        float DesplazamientoY = -1.8; // Arriba y abajo
        float DesplazamientoZ = 10; // Adelante y atrás
    glUniform4fv(escena.uColorLocation, 1, (const GLfloat *)colores[1]);
    glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
    glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1 + 3);

    glm::mat4 modelMatrix;
    glm::mat4 modelViewMatrix;

    // RUEDA DELANTERA DERECHA

   modelMatrix = glm::mat4(1.0f); // Matriz identidad
modelMatrix = glm::translate(modelMatrix, glm::vec3(tx + DesplazamientoX, ty - DesplazamientoY, tz +4.8));
modelMatrix = glm::translate(modelMatrix, glm::vec3(-DesplazamientoX, 0, -4.8));
modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(ry), glm::vec3(0, 1, 0));
modelMatrix = glm::translate(modelMatrix, glm::vec3(DesplazamientoX, 0, 4.8));
modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(rry), glm::vec3(0, 1, 0));
modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(rr), glm::vec3(1, 0, 0));
modelViewMatrix = escena.viewMatrix * modelMatrix;
glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]); // -> Envia nuestra ModelView al Vertex Shader
glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

    // RUEDA TRASERA DERECHA
  modelMatrix = glm::mat4(1.0f); // matriz identidad
modelMatrix = glm::translate(modelMatrix, glm::vec3(tx + DesplazamientoX, ty - DesplazamientoY, tz - DesplazamientoZ));
modelMatrix = glm::translate(modelMatrix, glm::vec3(-DesplazamientoX, 0, DesplazamientoZ));
modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(ry), glm::vec3(0, 1, 0));
modelMatrix = glm::translate(modelMatrix, glm::vec3(DesplazamientoX, 0, -DesplazamientoZ));
modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(rr), glm::vec3(1, 0, 0));
modelViewMatrix = escena.viewMatrix * modelMatrix;
// Envia nuestra ModelView al Vertex Shader
glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

    // RUEDA TRASERA IZQUIERDA
modelMatrix = glm::mat4(1.0f); // matriz identidad
modelMatrix = glm::translate(modelMatrix, glm::vec3(tx - DesplazamientoX, ty - DesplazamientoY, tz - DesplazamientoZ));
modelMatrix = glm::translate(modelMatrix, glm::vec3(DesplazamientoX, 0, DesplazamientoZ));
modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(ry), glm::vec3(0, 1, 0));
modelMatrix = glm::translate(modelMatrix, glm::vec3(-DesplazamientoX, 0, -DesplazamientoZ));
modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(rr), glm::vec3(1, 0, 0)); // en radianes
modelViewMatrix = escena.viewMatrix * modelMatrix;
// Envia nuestra ModelView al Vertex Shader
glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

    // RUEDA DELANTERA IZQUIERDA
   modelMatrix = glm::mat4(1.0f); // matriz identidad
modelMatrix = glm::translate(modelMatrix, glm::vec3(tx - DesplazamientoX, ty - DesplazamientoY, tz+4.8)); //Ponemos
modelMatrix = glm::translate(modelMatrix, glm::vec3(DesplazamientoX, 0, -4.8)); //Corrige al principio
modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(ry), glm::vec3(0, 1, 0)); //Rotacion de la rueda para simular si giro derecha o izq
modelMatrix = glm::translate(modelMatrix, glm::vec3(-DesplazamientoX, 0, 4.8)); // En principio corrige la posicion de la rueda al haber girado
modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(rry), glm::vec3(0, 1, 0)); // Simula el angulo de giro de la rueda
modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(rr), glm::vec3(1, 0, 0)); //Rotacion de la rueda para que gire
// modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(180.0), glm::vec3(0, 0, 1)); // Si tu rueda es igual x los dos lados te da igual
modelViewMatrix = escena.viewMatrix * modelMatrix;
// Envia nuestra ModelView al Vertex Shader
glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
}


    break;
}


        case SEMAFORO_ID: {
    if (escena.show_road) {  // Usamos show_road como control de visibilidad
        modelMatrix = glm::mat4(1.0f);  // Matriz identidad
        modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz+20));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(ry), glm::vec3(0, 1, 0));  // Rotaci�n

        modelViewMatrix = escena.viewMatrix * modelMatrix;

        // Enviar ModelView al Vertex Shader
        glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

        // Renderizar el sem�foro
        glUniform4fv(escena.uColorLocation, 1, colores[0]);
        glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0);
        glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0 + 3);

        glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
    }
    break;
}
    case BANCO_ID: {
    if (escena.show_road) {  // Usamos show_road como control de visibilidad
        modelMatrix = glm::mat4(1.0f);  // Matriz identidad
        modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(ry), glm::vec3(0, 1, 0));  // Rotaci�n

        modelViewMatrix = escena.viewMatrix * modelMatrix;

        // Enviar ModelView al Vertex Shader
        glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

        // Renderizar el banco
        glUniform4fv(escena.uColorLocation, 1, colores[0]);
        glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0);
        glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0 + 3);

        glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
    }
    break;
}
    case FAROLA_ID: {
        if(escena.show_road){
            // Renderizado de la farola
            modelMatrix = glm::mat4(1.0f);  // Matriz identidad
            modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));  // Posici�n
            modelMatrix = glm::rotate(modelMatrix, glm::radians(ry), glm::vec3(0, 1, 0));  // Rotaci�n

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Enviar matriz y color al shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
            glUniform4fv(escena.uColorLocation, 1, colores[0]);

            // Enviar atributos y dibujar
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0 + 3);

            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
        }
            break;
        }

        case CONTENEDOR_ID: {
            if(escena.show_road){
            // Renderizado del contenedor
            modelMatrix = glm::mat4(1.0f);  // Matriz identidad
            modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));  // Posici�n
            modelMatrix = glm::rotate(modelMatrix, glm::radians(ry), glm::vec3(0, 1, 0));  // Rotaci�n

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Enviar matriz y color al shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
            glUniform4fv(escena.uColorLocation, 1, colores[0]);

            // Enviar atributos y dibujar
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0 + 3);

            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }

        case BUZON_ID: {
            if(escena.show_road){
            // Renderizado del buz�n
            modelMatrix = glm::mat4(1.0f);  // Matriz identidad
            modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));  // Posici�n
            modelMatrix = glm::rotate(modelMatrix, glm::radians(ry), glm::vec3(0, 1, 0));  // Rotaci�n

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Enviar matriz y color al shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
            glUniform4fv(escena.uColorLocation, 1, colores[0]);

            // Enviar atributos y dibujar
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0 + 3);

            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
            case FUENTE_ID: { 
                if(escena.show_road){
                     // Renderizar la fuente
    modelMatrix = glm::mat4(1.0f);  // Matriz identidad
    modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));  // Posici�n
    modelMatrix = glm::rotate(modelMatrix, glm::radians(ry), glm::vec3(0, 1, 0));  // Rotaci�n

    modelViewMatrix = escena.viewMatrix * modelMatrix;

    // Enviar matriz y color al shader
    glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
    glUniform4fv(escena.uColorLocation, 1, colores[0]);

    // Enviar atributos y dibujar
    glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0);
    glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0 + 3);

    glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
                }
    break;
}

case STOP_ID: {  
    if(escena.show_road){
        // Renderizar el stop
    modelMatrix = glm::mat4(1.0f);  // Matriz identidad
    modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));  // Posici�n
    modelMatrix = glm::rotate(modelMatrix, glm::radians(ry), glm::vec3(0, 1, 0));  // Rotaci�n

    modelViewMatrix = escena.viewMatrix * modelMatrix;

    // Enviar matriz y color al shader
    glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
    glUniform4fv(escena.uColorLocation, 1, colores[0]);

    // Enviar atributos y dibujar
    glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0);
    glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0 + 3);

    glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
    }
    break;
}
case MARCADOR_ID: {

    if (escena.seleccion == 1 || escena.seleccion == 2 ) { // Mostrar solo si se selecciona un coche
        modelMatrix = glm::mat4(1.0f);  // Matriz identidad
    if (escena.seleccion != -1) {
        // Obtener el coche seleccionado
        TPrimitiva* car = escena.GetCar(escena.seleccion);
        if (car != NULL) {
            // 1. Aplica la traslación global del coche
            modelMatrix = glm::translate(modelMatrix, glm::vec3(car->tx, car->ty, car->tz));

            // 2. Aplica la rotación global del coche
            modelMatrix = glm::rotate(modelMatrix, glm::radians(car->ry), glm::vec3(0, 1, 0));

            // 3. Posiciona el marcador encima del coche
          modelMatrix = glm::translate(modelMatrix, glm::vec3(car->marcadorOffsetX, car->marcadorOffsetY, car->marcadorOffsetZ));

           }
    }else {
    // No hay selección activa
    std::cout << "Ningun objeto seleccionado." << std::endl;
}

        // 4. Calcula la matriz de modelo-vista
        modelViewMatrix = escena.viewMatrix * modelMatrix;

        // 5. Enviar la matriz de transformación al shader
        glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
        glUniform4fv(escena.uColorLocation, 1, colores[3]); // Color del marcador

        // 6. Dibujar el marcador
        glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0);
        glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, STRIDE, modelo0 + 3);

        glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
    }

    break;
}






    } // switch

}
void TPrimitiva::Reset() {
    switch (tipo) {
      case COCHE_ID:
            if (ID == 1) { // Carro 1
                tx = 7.5911f;
                tz = -66.035f;
            } else if (ID == 2) { // Carro 2
                tx = -11.41f;
                tz = -66.035f;
            }
            ty = 0.0f;
            rx = ry = rz = 0.0f;
            rr = rry = 0.0f; // Reseteo de ruedas
            break;

        case CARRETERA_ID:
            tx = ty = tz = 0.0f;
            ry = 0.0f;
            break;

        case EDIFICIO_ID:
            // Personalización de posición para cada edificio
            if (ID == 1) { // Edificio 1
                tx = -110.0f;
                tz = -110.0f;
                ry = 0.0f;
            } else if (ID == 2) { // Edificio 2
                tx = 110.0f;
                tz = 110.0f;
                ry = 180.0f;
            } else if (ID == 3) { // Edificio 3
                tx = -110.0f;
                tz = 110.0f;
                ry = 90.0f;
            } else if (ID == 4) { // Edificio 4
                tx = 110.0f;
                tz = -110.0f;
                ry = -90.0f;
            }
            ty = 0.0f; // Común para todos los edificios
            break;

        case SEMAFORO_ID:
            tx = 0.0f;
            ty = 0.0f;
            tz = -20.0f;
            ry = 90.0f;
            break;

        case BANCO_ID:
        case FAROLA_ID:
        case CONTENEDOR_ID:
        case BUZON_ID:
        case FUENTE_ID:
        case STOP_ID:
            tx = 0.0f;
            ty = 0.0f;
            tz = 0.0f;
            ry = 0.0f;
            break;

        case MARCADOR_ID:
            tx = 0.0f;
            ty = 0.0f;
            tz = 0.0f;
            ry = 0.0f;
            marcadorOffsetX = 0.0f;
            marcadorOffsetY = -0.50f;
            marcadorOffsetZ = 7.0f;
            break;

        default:
            tx = ty = tz = 0.0f;
            ry = 0.0f;
            break;
    }
}



//************************************************************** Clase TEscena

TEscena::TEscena()
       {

        carAngle=0;
    camara = 0;
    seleccion = -1;
    num_objects = 0;
    num_cars = 0;

    show_car = 1;
    show_wheels = 1;
    show_road = 1;

    // live variables usadas por GLUI en TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 0;

    scale = 100.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    rotationX = 0.0f;
rotationY = 0.0f;
zoom = 40.0f; // Zoom inicial
translationX = 0.0f;
translationY = 5.0f;






    memcpy(view_position, view_position_c, 3*sizeof(float));
    memcpy(view_rotate, view_rotate_c, 16*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));
    memcpy(light0_diffuse, light0_diffuse_c, 4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient, light1_ambient_c, 4*sizeof(float));
    memcpy(light1_diffuse, light1_diffuse_c, 4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(light2_ambient, light2_ambient_c, 4 * sizeof(float));
    memcpy(light2_diffuse, light2_diffuse_c, 4 * sizeof(float));
    memcpy(light2_specular, light2_specular_c, 4 * sizeof(float));
    memcpy(light2_position, light2_position_c, 4 * sizeof(float));

    memcpy(mat_ambient, mat_ambient_c, 4*sizeof(float));
    memcpy(mat_diffuse, mat_diffuse_c, 4*sizeof(float));
    memcpy(mat_specular, mat_specular_c, 4*sizeof(float));
    memcpy(mat_shininess, mat_shininess_c, 1*sizeof(float));
}



void __fastcall TEscena::InitGL()
{
    int tx, ty, tw, th;

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Inicializaci�n de GLEW
    std::cout << "Inicializando GLEW" << std::endl << std::endl;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendedor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Carga de los Shaders
    std::cout << std::endl << "Cargando Shaders" << std::endl;

    Shader shader;

    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("../../Shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    //std::cout << "Vertex Shader: " << shader.ReturnShaderID() << std::endl;
    shaders.push_back(shader.LoadShader("../../Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));
    //std::cout << "Fragment Shader: " << shader.ReturnShaderID() << std::endl;
    shaderProgram = new Program(shaders);

    //std::cout << "Shader Program: " << shaderProgram->ReturnProgramID() << std::endl;

    glUseProgram(shaderProgram->ReturnProgramID());
    //glValidateProgram(shaderProgram->ReturnProgramID());

    aPositionLocation=shaderProgram->attrib(A_POSITION);
    aNormalLocation=shaderProgram->attrib(A_NORMAL);

    uProjectionMatrixLocation=shaderProgram->uniform(U_PROJECTIONMATRIX);
    uMVMatrixLocation=shaderProgram->uniform(U_MVMATRIX);
    uVMatrixLocation=shaderProgram->uniform(U_VMATRIX);
    uColorLocation=shaderProgram->uniform(U_COLOR);
    uLuz0Location=shaderProgram->uniform(U_LUZ0);
    uLuz1Location = shaderProgram->uniform(U_LUZ1);
    uLuz2Location = shaderProgram->uniform(U_LUZ2);

    uIntensidadLuz0Location = shaderProgram->uniform("uIntensidad0");
    uIntensidadLuz1Location = shaderProgram->uniform("uIntensidad1");
    uIntensidadLuz2Location = shaderProgram->uniform("uIntensidad2");


    uPositionLuz0Location = shaderProgram->uniform("uPositionLuz0");
    uPositionLuz1Location = shaderProgram->uniform("uPositionLuz1");
    uPositionLuz2Location = shaderProgram->uniform("uPositionLuz2");
    /*
    std::cout << "a_Position Location: " << aPositionLocation << std::endl;
    std::cout << "a_Normal Location: " << aNormalLocation << std::endl;

    std::cout << "u_ProjectionMatrix Location: " << uProjectionMatrixLocation << std::endl;
    std::cout << "u_MVMatrix Location: " << uMVMatrixLocation << std::endl;
    std::cout << "u_VMatrix Location: " << uVMatrixLocation << std::endl;
    std::cout << "u_Color Location: " << uColorLocation << std::endl;
    std::cout << "u_Luz0 Location: " << uLuz0Location << std::endl;
    */

    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(aPositionLocation);
    glEnableVertexAttribArray(aNormalLocation);

    // Estableciendo la matriz de proyecci�n perspectiva
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    xy_aspect = (float)tw / (float)th;
    projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glEnable(GL_STENCIL_TEST);
glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}


/************************** TEscena::AddCar(TPrimitiva *car) *****************/

void __fastcall TEscena::AddCar(TPrimitiva *car)
{
    cars[num_cars] = car;
    num_cars++;
}

/******************** TEscena::AddObject(TPrimitiva *object) *****************/

void __fastcall TEscena::AddObject(TPrimitiva *object)
{
    objects[num_objects] = object;
    num_objects++;
}

/******************** TPrimitiva *TEscena::GetCar(int id) ********************/


TPrimitiva __fastcall *TEscena::GetCar(int id)
{
    TPrimitiva *p=NULL;

    for (int i=0; i<num_cars; i++)
    {
        if (cars[i]->ID==id)
        {
            p = cars[i];


        }

    }
    return(p);
}


/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderCars(bool reflejo) {

    for (int i=0; i<num_cars; i++)
    {
          glStencilFunc(GL_ALWAYS, cars[i]->ID, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        cars[i]->Render(seleccion, reflejo);
    }
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderObjects(bool reflejo) {

    for (int i=0; i<num_objects; i++)
    {
        objects[i]->Render(seleccion, reflejo);
    }
}


/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render()
{


    glm::mat4 rotateMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUniform1i(uLuz0Location, gui.light0_enabled);
    glUniform1i(uLuz1Location, gui.light1_enabled);
    glUniform1i(uLuz2Location, gui.light2_enabled);

    glUniform1f(uIntensidadLuz0Location, gui.light0_intensity);
    glUniform1f(uIntensidadLuz1Location, gui.light1_intensity);
    glUniform1f(uIntensidadLuz2Location, gui.light2_intensity);

    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!

    glUniform4fv(escena.uPositionLuz0Location, 1,(const GLfloat *) &escena.light0_position);
    glUniform4fv(escena.uPositionLuz1Location, 1,(const GLfloat *) &escena.light1_position);
    glUniform4fv(escena.uPositionLuz2Location, 1,(const GLfloat *) &escena.light2_position);

    int tx, ty, tw, th;
GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
xy_aspect = (float)tw / (float)th;
if(proyeccion==0){
projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);
}else{
escena.projectionMatrix = glm::ortho(-10.0f*escena.xy_aspect, 10.0f*escena.xy_aspect, -10.0f, 10.0f, -100.0f, 100.0f);
}
glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

     if(wireframe == 0){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }else if (wireframe == 1){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    // Z-buffer ---------------------------------------------------
if(z_buffer == 1){
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
}
else{
glDisable(GL_DEPTH_TEST);
}
// Culling ---------------------------------------------------
if(culling == 1){
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);
}
else{
glDisable(GL_CULL_FACE);
}
// Sentido ---------------------------------------------------
if(sentido == 1){
glFrontFace(GL_CCW);
}
else{
glFrontFace(GL_CW);
}

 viewMatrix = glm::mat4(1.0f);
 rotateMatrix = glm::make_mat4(view_rotate);
 viewMatrix = glm::translate(viewMatrix, glm::vec3(view_position[0], view_position[1], view_position[2]));
 viewMatrix = viewMatrix * rotateMatrix;
 viewMatrix = glm::scale(viewMatrix, glm::vec3(scale / 100, scale / 100, scale / 100));

 if (camara == 0) {
    // Matriz inicial de vista
    viewMatrix = glm::mat4(1.0f);

    // Calcular posición de la cámara
    glm::vec3 cameraPosition = glm::vec3(translationX, translationY, zoom);

    // Calcular el vector de dirección basado en las rotaciones
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotación en X
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación en Y

    // El vector hacia adelante (dirección inicial de la cámara en el espacio local)
    glm::vec4 forwardVector = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f); // Mirar hacia -Z

    // Aplicar rotación al vector de dirección
    glm::vec3 direction = glm::vec3(rotationMatrix * forwardVector);

    // Calcular el foco basado en la dirección y la posición de la cámara
    glm::vec3 cameraFocus = cameraPosition + direction;

    // Vector de "arriba" de la cámara
    glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

    // Configurar la matriz de vista con glm::lookAt
    viewMatrix = glm::lookAt(cameraPosition, cameraFocus, upDirection);

    // Enviar la matriz de vista al shader
    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}




if (camara == 1) {

    TPrimitiva* car = GetCar(escena.seleccion); // Get the selected car
    if (car != NULL) {
       // Get the car's position and rotation angle
        glm::vec3 carPosition(car->tx, car->ty, car->tz);
        float carAngle = glm::radians(escena.carAngle); // Convert car angle to radians
          // Get the car's position and rotation angle
        // Offset the camera's position behind and above the car
        glm::vec3 cameraOffset(-40.0f * glm::sin(carAngle), 100.0f, -50.0f * glm::cos(carAngle));
        glm::vec3 cameraPosition = carPosition + cameraOffset;

        // Define the camera focus (center of the car) and the up direction
        glm::vec3 cameraFocus = carPosition;
        glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

        // Update the view matrix using the lookAt function
        viewMatrix = glm::lookAt(
            cameraPosition, // Camera position
            cameraFocus,    // Focus on the car
            upDirection     // Up direction
        );

        // Pass the updated view matrix to the shader
        glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    } else {
        // Default aerial view if no car is selected
        glm::vec3 cameraPosition = glm::vec3(0.0f, 50.0f, 50.0f);
        glm::vec3 cameraFocus = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

        viewMatrix = glm::lookAt(cameraPosition, cameraFocus, upDirection);

        // Pass the updated view matrix to the shader
        glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    }
}

if (camara == 2) { // Cámara de seguimiento

    // Obtener el coche seleccionado
    TPrimitiva* car = GetCar(escena.seleccion);
    if (car != NULL) {
        // Posición del coche
        glm::vec3 carPosition(car->tx, car->ty, car->tz);

        // Rotación del coche
        float carRotation = glm::radians(car->ry);

        // Offset de la cámara basado en la rotación del coche
        glm::vec3 cameraOffset(-40.0f * glm::sin(carRotation), 50.0f, -50.0f * glm::cos(carRotation));
        glm::vec3 cameraPosition = carPosition + cameraOffset;

        // Punto de enfoque (centro del coche)
        glm::vec3 cameraFocus = carPosition;

        // Vector de dirección "arriba" (up)
        glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

        // Configurar la matriz de vista usando lookAt
        viewMatrix = glm::lookAt(
            cameraPosition, // Posición de la cámara
            cameraFocus,    // Punto de enfoque
            upDirection     // Dirección "arriba"
        );

        // Enviar la matriz de vista actualizada al shader
        glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    } else {
        // Si no hay coche seleccionado, cámara aérea por defecto
        glm::vec3 cameraPosition = glm::vec3(0.0f, 50.0f, 50.0f);
        glm::vec3 cameraFocus = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

        viewMatrix = glm::lookAt(cameraPosition, cameraFocus, upDirection);
        glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    }
}
  //A�adimos lo que hace cada vista para qeu en cada caso haga lo que debe con un if else


    glUniform1i(uLuz0Location, gui.light0_enabled);
    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!

    // Dibujar carretera y objetos
    RenderObjects(seleccion);

    // Dibujar coches
    RenderCars(seleccion);

    glutSwapBuffers();
    // En TEscena::Render() (Objects.cpp)

 }


// Selecciona un objeto a trav�s del rat�n
void __fastcall TEscena::Pick3D(int mouse_x, int mouse_y) {
    // Obtener las dimensiones del viewport
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    // Calcular la posici�n del rat�n en coordenadas OpenGL (invertir Y)
    int y_invertido = viewport[3] - mouse_y - 1;

    // Leer el ID desde el Stencil Buffer en la posici�n del rat�n
    GLuint pickedID;
    glReadPixels(mouse_x, y_invertido, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &pickedID);

    // Comprobar si el ID es v�lido
    if (pickedID > 0) {
        seleccion = pickedID; // Actualizar el ID seleccionado
    } else {
        seleccion = -1; // Sin selecci�n
    }

    // Forzar redibujado para reflejar los cambios
    glutPostRedisplay();
}

// Crea todo el escenario
void __fastcall TEscena::CrearEscenario()
{


    // Carretera
    TPrimitiva *road = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);


    // Coche
    TPrimitiva *car1 = new TPrimitiva(1, COCHE_ID);
    TPrimitiva *car2 = new TPrimitiva(2, COCHE_ID);
    car1->colores[0][0] = 1.0f; // Rojo
    car1->colores[0][1] = 0.0f;
    car1->colores[0][2] = 0.0f;
    car1->colores[0][3] = 1.0f; // Opacidad completa

    car2->colores[0][0] = 0.0f; // Azul
    car2->colores[0][1] = 0.0f;
    car2->colores[0][2] = 1.0f;
    car2->colores[0][3] = 1.0f;


    // Edificios
    TPrimitiva *edificio1 = new TPrimitiva(EDIFICIO_ID, EDIFICIO_ID);
    TPrimitiva *edificio2 = new TPrimitiva(EDIFICIO_ID, EDIFICIO_ID);
    TPrimitiva *edificio3 = new TPrimitiva(EDIFICIO_ID, EDIFICIO_ID);
    TPrimitiva *edificio4 = new TPrimitiva(EDIFICIO_ID, EDIFICIO_ID);

    edificio1->colores[0][0] = 0.5f; // Morado
    edificio1->colores[0][1] = 0.0f;
    edificio1->colores[0][2] = 0.5f;
    edificio1->colores[0][3] = 1.0f;

    edificio2->colores[0][0] = 1.0f; // Naranja
    edificio2->colores[0][1] = 0.5f;
    edificio2->colores[0][2] = 0.0f;
    edificio2->colores[0][3] = 1.0f;

    edificio3->colores[0][0] = 0.0f; // Verde oscuro
    edificio3->colores[0][1] = 0.5f;
    edificio3->colores[0][2] = 0.0f;
    edificio3->colores[0][3] = 1.0f;

    edificio4->colores[0][0] = 0.0f; // Cian
    edificio4->colores[0][1] = 0.5f;
    edificio4->colores[0][2] = 1.0f;
    edificio4->colores[0][3] = 1.0f;
// Otros objetos: sem�foro, banco, farola, contenedor, buz�n, fuente, stop
    TPrimitiva *semaforo = new TPrimitiva(SEMAFORO_ID, SEMAFORO_ID);
    TPrimitiva *banco = new TPrimitiva(BANCO_ID, BANCO_ID);
    TPrimitiva *farola = new TPrimitiva(FAROLA_ID, FAROLA_ID);
    TPrimitiva *contenedor = new TPrimitiva(CONTENEDOR_ID, CONTENEDOR_ID);
    TPrimitiva *buzon = new TPrimitiva(BUZON_ID, BUZON_ID);
    TPrimitiva *fuente = new TPrimitiva(FUENTE_ID, FUENTE_ID);
    TPrimitiva *stop = new TPrimitiva(STOP_ID, STOP_ID);
    TPrimitiva* marcador = new TPrimitiva(MARCADOR_ID, MARCADOR_ID);

    semaforo->colores[0][0] = 0.5f; // Gris
    semaforo->colores[0][1] = 0.5f;
    semaforo->colores[0][2] = 0.5f;
    semaforo->colores[0][3] = 1.0f;

    banco->colores[0][0] = 0.6f; // Marrón
    banco->colores[0][1] = 0.3f;
    banco->colores[0][2] = 0.0f;
    banco->colores[0][3] = 1.0f;

    farola->colores[0][0] = 0.8f; // Gris claro
    farola->colores[0][1] = 0.8f;
    farola->colores[0][2] = 0.8f;
    farola->colores[0][3] = 1.0f;

    contenedor->colores[0][0] = 0.0f; // Verde
    contenedor->colores[0][1] = 1.0f;
    contenedor->colores[0][2] = 0.0f;
    contenedor->colores[0][3] = 1.0f;

    buzon->colores[0][0] = 1.0f; // Amarillo
    buzon->colores[0][1] = 1.0f;
    buzon->colores[0][2] = 0.0f;
    buzon->colores[0][3] = 1.0f;

    fuente->colores[0][0] = 0.6f; // Gris oscuro
    fuente->colores[0][1] = 0.6f;
    fuente->colores[0][2] = 0.6f;
    fuente->colores[0][3] = 1.0f;

    marcador->colores[0][0] = 1.0f; // Amarillo
    marcador->colores[0][1] = 1.0f;
    marcador->colores[0][2] = 0.0f;
    marcador->colores[0][3] = 1.0f;

     car2->tx = -11.41f; // Posici�n inicial del segundo coche
    car2->tz = -66.035f;
    // Personalizaci�n de posici�n y rotaci�n para edificios
    edificio1->tx = -110.0f; edificio1->tz = -110.0f; edificio1->ry = 0.0f;
    edificio2->tx =  110.0f; edificio2->tz =  110.0f; edificio2->ry = 180.0f;
    edificio3->tx = -110.0f; edificio3->tz =  110.0f; edificio3->ry = 90.0f;
    edificio4->tx =  110.0f; edificio4->tz = -110.0f; edificio4->ry = -90.0f;




    AddObject(road);
    AddCar(car1);
    AddCar(car2);


    AddObject(edificio1);
    AddObject(edificio2);
    AddObject(edificio3);
    AddObject(edificio4);


AddObject(marcador);

    // Personalizaci�n de posici�n para sem�foro
    semaforo->tz = -20.0f; semaforo->ry = 90.0f;

    // A�adir los objetos
    AddObject(semaforo);
    AddObject(banco);
    AddObject(farola);
    AddObject(contenedor);
    AddObject(buzon);
    AddObject(fuente);
    AddObject(stop);
}


//************************************************************** Clase TGui

TGui::TGui()
{
    globalModifiers = 0; // Estado global de teclas modificadoras

    sel = 0;
    enable_panel2 = 1;
    light0_enabled = 1;
    light1_enabled = 0;
    light2_enabled = 0;
    light0_intensity = 0.8;
    light1_intensity = 0.8;
    light2_intensity = 0.8;
    lastMouseX = 0;
lastMouseY = 0;
mouseButton = -1;
    memcpy(light0_position, light0_position_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));
    memcpy(light2_position, light2_position_c, 4*sizeof(float));
}

void controlCallback(int control)
{
    gui.ControlCallback(control);
}

void __fastcall TGui::Init(int main_window) {

    /****************************************************/
    /*        C�digo con el interfaz Gr�fico GLUI       */
    /****************************************************/
    printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

    window_id = main_window;

    /*** Crea a ventana lateral ***/
    glui = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_RIGHT );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    // A�ade un panel con texto con el valor de la selecci�n
    GLUI_Panel *panel0 = new GLUI_Panel(glui, "Seleccion");
    GLUI_RadioGroup *radioGroup = new GLUI_RadioGroup(panel0, &sel, SEL_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroup, "NINGUNO");
    glui->add_radiobutton_to_group(radioGroup, "COCHE 1");
    glui->add_radiobutton_to_group(radioGroup, "COCHE 2");

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    // Creamos el rollout (glui,nombre,booleano si lo queremos activo o no )
 GLUI_Panel *camara = new GLUI_Rollout(glui, "Tipos de camara", true);
//Creamos el menu (Panel al que lo queremos colocar,valor que coje,indentificador,controllcallback)
 GLUI_RadioGroup *radioCamara = new GLUI_RadioGroup(camara, &aCamara, MODO_CAMARA_ID, controlCallback);
//A�adimos las opciones que queremos
 glui->add_radiobutton_to_group(radioCamara, "Clasica");
 glui->add_radiobutton_to_group(radioCamara, "Aerea");
 glui->add_radiobutton_to_group(radioCamara, "Seguimiento");

    new GLUI_StaticText( glui, "" );

    GLUI_Panel *proyeccion = new GLUI_Panel(glui, "Proyeccion");
GLUI_RadioGroup *radioProyeccion = new GLUI_RadioGroup(proyeccion, &a_Proyeccion, PROYECCION_ID, controlCallback);
glui->add_radiobutton_to_group(radioProyeccion, "Perspectiva");
glui->add_radiobutton_to_group(radioProyeccion, "Paralela");
    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    obj_panel = new GLUI_Rollout(glui, "Propiedades", true );

    /***** Control para las propiedades de escena *****/

    // Creamos el rollout (glui,nombre,booleano si lo queremos activo o no )
GLUI_Panel *vista = new GLUI_Rollout(glui, "Modo de vista", false);
//Creamos el menu (Panel al que lo queremos colocar,valor que coje,indentificador,controllcallback)
GLUI_RadioGroup *radioGroupVista = new GLUI_RadioGroup(vista, &aVista, MODO_VISTA, controlCallback);
//Añadimos las opciones que queremos
glui->add_radiobutton_to_group(radioGroupVista, "Solido");
glui->add_radiobutton_to_group(radioGroupVista, "Aristas");
glui->add_radiobutton_to_group(radioGroupVista, "Puntos");
    glui->add_column_to_panel(obj_panel, true);
    new GLUI_Checkbox( obj_panel, "Culling", &escena.culling, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Z Buffer", &escena.z_buffer, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Horario-AntiHorario", &escena.sentido, 1, controlCallback );
    /******** A�ade controles para las luces ********/

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Luces", true );

    GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Luz 1" );
    GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Luz 2" );
    GLUI_Panel *light2 = new GLUI_Panel(roll_lights, "Luz 3");

    new GLUI_Checkbox( light0, "Encendida", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback );
    light0_spinner = new GLUI_Spinner( light0, "Intensidad:", &light0_intensity,
                            LIGHT0_INTENSITY_ID, controlCallback );
    light0_spinner->set_float_limits( 0.0, 1.0 );
    GLUI_Scrollbar *sb;
    sb = new GLUI_Scrollbar( light0, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[0],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[1],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[2],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_Checkbox(light1, "Encendida", &light1_enabled, LIGHT1_ENABLED_ID, controlCallback);
    light1_spinner = new GLUI_Spinner(light1, "Intensidad:", &light1_intensity,LIGHT1_INTENSITY_ID, controlCallback);
    light1_spinner->set_float_limits(0.0, 1.0);

    sb = new GLUI_Scrollbar(light1, "X", GLUI_SCROLL_HORIZONTAL,
    &escena.light1_position[0], LIGHT1_POSITION_ID, controlCallback);

    sb->set_float_limits(-100, 100);

    sb = new GLUI_Scrollbar(light1, "Y", GLUI_SCROLL_HORIZONTAL,
    &escena.light1_position[1], LIGHT1_POSITION_ID, controlCallback);

    sb->set_float_limits(-100, 100);

    sb = new GLUI_Scrollbar(light1, "Z", GLUI_SCROLL_HORIZONTAL,
    &escena.light1_position[2], LIGHT1_POSITION_ID, controlCallback);

    sb->set_float_limits(-100, 100);

    new GLUI_Checkbox(light2, "Encendida", &light2_enabled, LIGHT2_ENABLED_ID, controlCallback);
    light2_spinner = new GLUI_Spinner(light2, "Intensidad:", &light2_intensity,
                            LIGHT2_INTENSITY_ID, controlCallback);

    light2_spinner->set_float_limits(0.0, 1.0);

    sb = new GLUI_Scrollbar(light2, "X", GLUI_SCROLL_HORIZONTAL,
    &escena.light2_position[0], LIGHT2_POSITION_ID, controlCallback);

    sb->set_float_limits(-100, 100);

    sb = new GLUI_Scrollbar(light2, "Y", GLUI_SCROLL_HORIZONTAL,
    &escena.light2_position[1], LIGHT2_POSITION_ID, controlCallback);

    sb->set_float_limits(-100, 100);

    sb = new GLUI_Scrollbar(light2, "Z", GLUI_SCROLL_HORIZONTAL,
    &escena.light2_position[2], LIGHT2_POSITION_ID, controlCallback);

    sb->set_float_limits(-100, 100);




    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    /***  Rollout de Opciones ***/
    GLUI_Rollout *options = new GLUI_Rollout(glui, "Opciones", false );
    new GLUI_Checkbox( options, "Dibujar Coche", &escena.show_car );
    new GLUI_Checkbox( options, "Dibujar Ruedas", &escena.show_wheels );
    new GLUI_Checkbox( options, "Dibujar Escena", &escena.show_road );

    /*** Disable/Enable botones ***/
   
    new GLUI_StaticText( glui, "" );
    new GLUI_Button( glui, "Resetear Posicion", RESET_ID, controlCallback );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

     // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_StaticText( glui, "  Autor:" );
    new GLUI_StaticText( glui, "  2012-2022 (C) Juan Antonio Puchol  " );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    /****** A 'quit' button *****/
    new GLUI_Button( glui, "Salir", 0,(GLUI_Update_CB)exit );

    // Crea la subventana inferior
    glui2 = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_BOTTOM );

    /**** Link windows to GLUI, and register idle callback ******/
    glui->set_main_gfx_window( window_id );
    glui2->set_main_gfx_window( window_id );

   view_rot = new GLUI_Rotation(glui2, "Rotacion Escena", escena.view_rotate);
view_rot->set_spin(1.0);
new GLUI_Column(glui2, false);
GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Traslacion Escena XY", GLUI_TRANSLATION_XY, escena.view_position);
trans_xy->set_speed(.005);
new GLUI_Column(glui2, false);
GLUI_Translation *trans_x = new GLUI_Translation(glui2, "Traslacion Escena X", GLUI_TRANSLATION_X, escena.view_position);
trans_x->set_speed(.005);
new GLUI_Column(glui2, false);
GLUI_Translation *trans_y = new GLUI_Translation(glui2, "Traslacion Escena Y", GLUI_TRANSLATION_Y, &escena.view_position[1]);
trans_y->set_speed(.005);
new GLUI_Column(glui2, false);
GLUI_Translation *trans_z = new GLUI_Translation(glui2, "Traslacion Escena Z", GLUI_TRANSLATION_Z, &escena.view_position[2]);
trans_z->set_speed(.005);
}


/**************************************** TGui::ControlCallback() *******************/

void __fastcall TGui::ControlCallback( int control )
{
    switch (control) {
        case LIGHT0_ENABLED_ID: {
            if ( light0_enabled )
                light0_spinner->enable();
            else
                light0_spinner->disable();
            break;
        }
        case LIGHT1_ENABLED_ID: {
            if ( light1_enabled )
                light1_spinner->enable();
            else
                light1_spinner->disable();
            break;
        }
        case LIGHT0_INTENSITY_ID: {

            float v[] = {
                escena.light0_diffuse[0],  escena.light0_diffuse[1],
                escena.light0_diffuse[2],  escena.light0_diffuse[3] };

            v[0] *= light0_intensity;
            v[1] *= light0_intensity;
            v[2] *= light0_intensity;
            break;
        }
        case LIGHT1_INTENSITY_ID: {

            float v[] = {
                escena.light1_diffuse[0],  escena.light1_diffuse[1],
                escena.light1_diffuse[2],  escena.light1_diffuse[3] };

            v[0] *= light1_intensity;
            v[1] *= light1_intensity;
            v[2] *= light1_intensity;
            break;
        }
        case ENABLE_ID: {
            glui2->enable();
            break;
        }
        case DISABLE_ID: {
            glui2->disable();
            break;
        }
        case RESET_ID: {
    memcpy(escena.view_position, view_position_c, 3 * sizeof(float));
    view_rot->reset();
    escena.scale = 100.0;

    // Resetear todos los objetos
    for (int i = 0; i < escena.num_objects; i++) {
        escena.objects[i]->Reset();
    }
    for (int i = 0; i < escena.num_cars; i++) {
        escena.cars[i]->Reset();
    }

    glutPostRedisplay(); // Redibujar la escena
    break;
}
       case SEL_ID: {
    if (sel == 0) {
        escena.seleccion = -1; // Sin selección
    } else {
        escena.seleccion = sel; // Selecciona el coche correspondiente
    }
    glutSetWindow(glui->get_glut_window_id());
    break;
}
    case MODO_CAMARA_ID:
    {
     escena.camara = aCamara;
    glutSetWindow(glui->get_glut_window_id());
    // Forzar redibujado de la escena con la nueva c�mara
    glutPostRedisplay();
    break;
    }
    case MODO_VISTA:
    {
    escena.wireframe = aVista;
    glutSetWindow(glui->get_glut_window_id());
    break;
}
case PROYECCION_ID:{
escena.proyeccion = a_Proyeccion;
glutSetWindow(glui->get_glut_window_id());
break;
}


  } // switch
}

/***************************************** TGui::Idle() ***********/

void __fastcall TGui::Idle(void)
{
 /* According to the GLUT specification, the current window is
 undefined during an idle callback. So we need to explicitly change
 it if necessary */
 if (glutGetWindow() != window_id)
 glutSetWindow(window_id);
 GLUI_Master.sync_live_all();
 if (enable_panel2)
 glui2->enable();
 else
 glui2->disable();
 glutPostRedisplay();

}

/**************************************** TGui::reshape() *************/

void __fastcall TGui::Reshape( int xx, int yy )
{
    int x, y, ancho, alto;
    GLUI_Master.get_viewport_area( &x, &y, &ancho, &alto );
    glViewport( x, y, ancho, alto );

    // !!!!! ATENCI�N: comprobar que alto no sea 0, sino divisi�n por 0 !!!!!!
    escena.xy_aspect = (float)ancho / (float)alto;
    escena.projectionMatrix = glm::perspective(45.0f, escena.xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(escena.uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(escena.projectionMatrix));

    //std::cout << "xy aspect: " << escena.xy_aspect << std::endl;

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion(int x, int y) {
    int dx = x - lastMouseX; // Cambio en X
    int dy = y - lastMouseY; // Cambio en Y

    if (mouseButton == GLUT_LEFT_BUTTON) { // Rotación
        if (globalModifiers & GLUT_ACTIVE_CTRL) { // Rotación en eje Z con CTRL
            escena.rotationY += dx * 0.5f;
        } else { // Rotación en ejes X e Y
            escena.rotationX += dy * 0.5f;
            escena.rotationY += dx * 0.5f;
        }
    } else if (mouseButton == GLUT_RIGHT_BUTTON) { // Zoom
        if (globalModifiers & GLUT_ACTIVE_CTRL) { // Zoom en eje Z con CTRL
            escena.translationY -= dy * 0.1f;
        } else { // Zoom normal
            escena.zoom -= dy * 0.1f;
            if (escena.zoom < 1.0f) escena.zoom = 1.0f; // Límite mínimo de zoom
        }
    } else if (mouseButton == GLUT_LEFT_BUTTON){
        if(globalModifiers & GLUT_ACTIVE_SHIFT){
           escena.translationY += dy * 0.05f;
        } else { // Traslación en ejes X e Y
            escena.translationX += dx * 0.05f;
            escena.translationY -= dy * 0.05f;
        }

    }

    lastMouseX = x;
    lastMouseY = y;
    glutPostRedisplay(); // Redibujar la escena
}




/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y) {
    if (button_state == GLUT_DOWN) {
        mouseButton = button; // Guarda el botón presionado
        lastMouseX = x;
        lastMouseY = y;

        globalModifiers = glutGetModifiers(); // Detecta las teclas modificadoras


        escena.Pick3D(x, y); // Llama a la selección 3D
    } else {
        mouseButton = -1; // Ningún botón presionado
    }
}




