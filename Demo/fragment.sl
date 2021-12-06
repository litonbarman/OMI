#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

//uniform sampler2D texture_diffuse1;

// lighting
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;


void main()
{    
//    FragColor =  texture(texture_diffuse1, TexCoords); 
     
     // lighting
     
      float ambientStrength = 0.1;
      vec3 ambient = ambientStrength * lightColor;

      vec3 norm = normalize(Normal);
      vec3 lightDir = normalize(lightPos - FragPos);
      float diff = max(dot(norm, lightDir), 0.0);
      vec3 diffuse = diff * lightColor;

      float specularStrength = 0.5;
      vec3 viewDir = normalize(viewPos - FragPos);
      vec3 reflectDir = reflect(-lightDir, norm);

      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 252);      // 32 is nice
      vec3 specular = specularStrength * spec * lightColor;

      vec3 result = (ambient + diffuse + specular);

      vec4 color = vec4(result, 1.0);
     
     // lighting
     FragColor =  color ; //* texture(texture_diffuse1, TexCoords);
}