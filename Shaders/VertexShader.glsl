
attribute vec4 a_Position;	        // in: Posición de cada vértice
attribute vec3 a_Normal;	        // in: Normal de cada vértice

uniform mat4 u_ProjectionMatrix; 	// in: Matriz Projection
uniform mat4 u_MVMatrix;	        // in: Matriz ModelView
uniform mat4 u_VMatrix;             // in: Matriz View (cámara)
uniform vec4 u_Color;		        // in: Color del objeto
// Información de las luces
uniform int u_Luz0, u_Luz1, u_Luz2; // Estado de las luces (encendido/apagado)
uniform vec4 uPositionLuz0, uPositionLuz1, uPositionLuz2; // Posición de las luces
uniform float uIntensidad0, uIntensidad1, uIntensidad2; // Intensidad de las luces
uniform int u_ambient; // Estado de la iluminación ambiental
		        // out: Color al fragment shader

// Salidas del Vertex Shader
varying float v_Luz; // Intensidad de luz en el vértice
varying float v_specular; // Intensidad de luz especular en el vértice
varying vec4 v_Color; // Color resultante del vértice
void main()
{
    // Transformación de la posición de las luces a coordenadas de vista
    vec4 LightPos0 = u_VMatrix * uPositionLuz0;
    vec4 LightPos1 = u_VMatrix * uPositionLuz1;
    vec4 LightPos2 = u_VMatrix * uPositionLuz2;

    // Transformación de la posición y normal del vértice
    vec3 P = vec3(u_MVMatrix * a_Position); // Posición del vértice en coordenadas de vista
    vec3 N = normalize(vec3(u_MVMatrix * vec4(a_Normal, 0.0))); // Normal del vértice

	// Vector de vista (punto de vista hacia el vértice)
    vec3 viewVec = normalize(-P);



        // Cálculo de la iluminación ambiental
    float ambient = (u_ambient > 0) ? 0.30 : 0.0; // 30% de intensidad ambiente

	// Inicialización de la iluminación difusa y especular
    float diffuse0 = 0.0, specular0 = 0.0;
    float diffuse1 = 0.0, specular1 = 0.0;
    float diffuse2 = 0.0, specular2 = 0.0;

            // Cálculos de iluminación para Luz 0
    if (u_Luz0 > 0) {
        float d0 = length(LightPos0.xyz - P); // distancia de la luz
        vec3 L0 = normalize(LightPos0.xyz - P); // Vector Luz
        diffuse0 = max(dot(N, L0), 0.0); // Cálculo de la int. difusa

        // Cálculo de la atenuación
        float attenuation0 = 80.0 / (0.25 + (0.01 * d0) + (0.003 * d0 * d0));
        diffuse0 = diffuse0 * attenuation0 * uIntensidad0;
        vec3 lightVec0 = L0;
        vec3 reflectVec0 = reflect(-lightVec0, N);
        specular0 = clamp(dot(reflectVec0, viewVec), 0.0, 1.0);
        specular0 = pow(specular0, 5.0) * uIntensidad0;
        }

        // Cálculos de iluminación para Luz 1
    if (u_Luz1 > 0) {
        float d1 = length(LightPos1.xyz - P);
        vec3 L1 = normalize(LightPos1.xyz - P);
        diffuse1 = max(dot(N, L1), 0.0);
        float attenuation1 = 80.0 / (0.25 + (0.01 * d1) + (0.003 * d1 * d1));
        diffuse1 = diffuse1 * attenuation1 * uIntensidad1;
        vec3 lightVec1 = L1;
        vec3 reflectVec1 = reflect(-lightVec1, N);
        specular1 = clamp(dot(reflectVec1, viewVec), 0.0, 1.0);
        specular1 = pow(specular1, 5.0) * uIntensidad1;
        }

        // Cálculos de iluminación para Luz 2
    if (u_Luz2 > 0) {
        float d2 = length(LightPos2.xyz - P);
        vec3 L2 = normalize(LightPos2.xyz - P);
        diffuse2 = max(dot(N, L2), 0.0);
        float attenuation2 = 80.0 / (0.25 + (0.01 * d2) + (0.003 * d2 * d2));
        diffuse2 = diffuse2 * attenuation2 * uIntensidad2;
        vec3 lightVec2 = L2;
        vec3 reflectVec2 = reflect(-lightVec2, N);
        specular2 = clamp(dot(reflectVec2, viewVec), 0.0, 1.0);
        specular2 = pow(specular2, 5.0) * uIntensidad2;
        }
        // Sumatoria de componentes de iluminación
    v_specular = specular0 + specular1 + specular2;
    v_Luz = ambient + diffuse0 + diffuse1 + diffuse2;
    // Cálculo del color resultante del vértice
    v_Color = u_Color * v_Luz;
    // Transformación final del vértice
    gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
}
