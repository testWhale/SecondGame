#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;  

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

uniform Material material;
uniform Light light;  


vec4 spotLight(){
    vec3 DirFrmFragToLight = light.position - FragPos; //without norm u only get vector
    float dist = length(DirFrmFragToLight);
    DirFrmFragToLight = normalize(DirFrmFragToLight); // norm u get == 1.0

    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    // diffuse 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, DirFrmFragToLight), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-DirFrmFragToLight, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    float theta = dot(DirFrmFragToLight, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);       
   
    diffuse  *= intensity;
    specular *= intensity;
    diffuse *= attenuation;
    specular *= attenuation;
    vec3 debugColor = vec3(dot(DirFrmFragToLight, normalize(-light.direction)));

    vec3 result =  ambient + diffuse + specular ;
    return (vec4(result, 1.0));
    
}




void main()
{
    

    FragColor = vec4(Normal * 0.5 + 0.5, 1.0); 
    //FragColor = spotLight();
    //the FragColor is auto sent to the framebuffer color attachment

}