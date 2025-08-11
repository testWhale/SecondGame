#ifndef MODEL_H
#define MODEL_H
#include <glad/glad.h>
#include "stb/stb_image.h"

#include "shaderClass.h"
#include "mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include "assimp/scene.h" 
#include "assimp/postprocess.h"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model {
    public:
        // model data 
        std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh>    meshes;
        std::string directory;
        bool gammaCorrection;
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);

        // constructor, expects a filepath to a 3D model.
        Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
        {
            loadModel(path);
        }

        // draws the model, and thus all its meshes
        void Draw(Shader& shader)
        {
            for (unsigned int i = 0; i < meshes.size(); i++)
                meshes[i].Draw(shader);
			/*std::cout << "Model Drawn" << std::endl;*/
        }

        glm::mat4 getModelMatrix() const{
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
            model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
            model = glm::scale(model, glm::vec3(scale));
			return model;
        }
	private:

		// unknowns, how to load model
		// what is processNode? processMesh?
		// Why are we calling the texture again privately?
        void loadModel(std::string const& path)
        {
            // read file via ASSIMP
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
            // check for errors
            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
            {
                std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
                return;
            }
            // retrieve the directory path of the filepath
            directory = path.substr(0, path.find_last_of('/'));
			std::cout << "Model Directory: " << directory << std::endl;

            // process ASSIMP's root node recursively
            processNode(scene->mRootNode, scene);
        }

		void processNode(aiNode* node, const aiScene* scene)
		{
			// process all the node's meshes (if any)
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(processMesh(mesh, scene));
			}
			// then do the same for each of its children
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				processNode(node->mChildren[i], scene);
			}
		}

        Mesh processMesh(aiMesh* mesh, const aiScene* scene)
        {
            // data to fill
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            std::vector<Texture> textures;

            // walk through each of the mesh's vertices
            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                Vertex vertex;
                glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
                // positions
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                vertex.Position = vector;
                // normals
                if (mesh->HasNormals())
                {
                    vector.x = mesh->mNormals[i].x;
                    vector.y = mesh->mNormals[i].y;
                    vector.z = mesh->mNormals[i].z;
                    vertex.Normal = vector;
                }
                // texture coordinates
                if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
                {
                    glm::vec2 vec;
                    // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                    // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                    vec.x = mesh->mTextureCoords[0][i].x;
                    vec.y = mesh->mTextureCoords[0][i].y;
                    vertex.TexCoords = vec;
                    // tangent
                    vector.x = mesh->mTangents[i].x;
                    vector.y = mesh->mTangents[i].y;
                    vector.z = mesh->mTangents[i].z;
                    vertex.Tangent = vector;
                    // bitangent
                    vector.x = mesh->mBitangents[i].x;
                    vector.y = mesh->mBitangents[i].y;
                    vector.z = mesh->mBitangents[i].z;
                    vertex.Bitangent = vector;
                }
                else
                    vertex.TexCoords = glm::vec2(0.0f, 0.0f);

                vertices.push_back(vertex);
            }
            // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                // retrieve all indices of the face and store them in the indices vector
                for (unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }
            // process materials
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
            // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
            // Same applies to other texture as the following list summarizes:
            // diffuse: texture_diffuseN
            // specular: texture_specularN
            // normal: texture_normalN

            // 1. diffuse maps
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            // 2. specular maps
            std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            // 3. normal maps
            std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
            // 4. height maps
            std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
            textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

            // return a mesh object created from the extracted mesh data
            return Mesh(vertices, indices, textures);
        }

        // checks all material textures of a given type and loads the textures if they're not loaded yet.
        // the required info is returned as a Texture struct.
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
        {
            std::vector<Texture> textures;
            for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
            {
                aiString str;
                mat->GetTexture(type, i, &str);
                // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
                bool skip = false;
                for (unsigned int j = 0; j < textures_loaded.size(); j++)
                {
                    if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                    {
                        textures.push_back(textures_loaded[j]);
                        skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                        break;
                    }
                }
                if (!skip)
                {   // if texture hasn't been loaded already, load it
                    Texture texture;
                    texture.id = TextureFromFile(str.C_Str(), this->directory);
                    texture.type = typeName;
                    texture.path = str.C_Str();
                    textures.push_back(texture);
                    textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
                }
            }
            return textures;
        }
};



#endif
