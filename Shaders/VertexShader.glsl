
attribute vec4 a_Position;	        // in: Posici�n de cada v�rtice
attribute vec3 a_Normal;	        // in: Normal de cada v�rtice

uniform mat4 u_ProjectionMatrix; 	// in: Matriz Projection
uniform mat4 u_MVMatrix;	        // in: Matriz ModelView
uniform mat4 u_VMatrix;             // in: Matriz View (c�mara)
uniform vec4 u_Color;		        // in: Color del objeto
// Informaci�n de las luces
uniform int u_Luz0, u_Luz1, u_Luz2; // Estado de las luces (encendido/apagado)
uniform vec4 uPositionLuz0, uPositionLuz1, uPositionLuz2; // Posici�n de las luces
uniform float uIntensidad0, uIntensidad1, uIntensidad2; // Intensidad de las luces
uniform int u_ambient; // Estado de la iluminaci�n ambiental
		        // out: Color al fragment shader

// Salidas del Vertex Shader
varying float v_Luz; // Intensidad de luz en el v�rtice
varying float v_specular; // Intensidad de luz especular en el v�rtice
varying vec4 v_Color; // Color resultante del v�rtice
void main()
{
    // Transformaci�n de la posici�n de las luces a coordenadas de vista
    vec4 LightPos0 = u_VMatrix * uPositionLuz0;
    vec4 LightPos1 = u_VMatrix * uPositionLuz1;
    vec4 LightPos2 = u_VMatrix * uPositionLuz2;

    // Transformaci�n de la posici�n y normal del v�rtice
    vec3 P = vec3(u_MVMatrix * a_Position); // Posici�n del v�rtice en coordenadas de vista
    vec3 N = normalize(vec3(u_MVMatrix * vec4(a_Normal, 0.0))); // Normal del v�rtice

	// Vector de vista (punto de vista hacia el v�rtice)
    vec3 viewVec = normalize(-P);



        // C�lculo de la iluminaci�n ambiental
    float ambient = (u_ambient > 0) ? 0.30 : 0.0; // 30% de intensidad ambiente

	// Inicializaci�n de la iluminaci�n difusa y especular
    float diffuse0 = 0.0, specular0 = 0.0;
    float diffuse1 = 0.0, specular1 = 0.0;
    float diffuse2 = 0.0, specular2 = 0.0;

            // C�lculos de iluminaci�n para Luz 0
    if (u_Luz0 > 0) {
        float d0 = length(LightPos0.xyz - P); // distancia de la luz
        vec3 L0 = normalize(LightPos0.xyz - P); // Vector Luz
        diffuse0 = max(dot(N, L0), 0.0); // C�lculo de la int. difusa

        // C�lculo de la atenuaci�n
        float attenuation0 = 80.0 / (0.25 + (0.01 * d0) + (0.003 * d0 * d0));
        diffuse0 = diffuse0 * attenuation0 * uIntensidad0;
        vec3 lightVec0 = L0;
        vec3 reflectVec0 = reflect(-lightVec0, N);
        specular0 = clamp(dot(reflectVec0, viewVec), 0.0, 1.0);
        specular0 = pow(specular0, 5.0) * uIntensidad0;
        }

        // C�lculos de iluminaci�n para Luz 1
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

        // C�lculos de iluminaci�n para Luz 2
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
        // Sumatoria de componentes de iluminaci�n
    v_specular = specular0 + specular1 + specular2;
    v_Luz = ambient + diffuse0 + diffuse1 + diffuse2;
    // C�lculo del color resultante del v�rtice
    v_Color = u_Color * v_Luz;
    // Transformaci�n final del v�rtice
    gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
}
