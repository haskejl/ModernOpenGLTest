#include "Mesh.h"

namespace ssfw
{
	Mesh::Mesh()
	{
	}


	Mesh::~Mesh()
	{
		materials.~vector();
	}

	void Mesh::loadMesh(std::string filePath)
	{
		//Opening of block regex
		std::regex materialBlockStart("^\\s+<library_effects>");
		std::regex vertexBlockStart("^\\s+<source.+positions.+>");
		std::regex triangleBlockStart("^\\s+<triangles.+>");

		//Closing of block regex
		std::regex materialBlockEnd("^\\s+</library_effects>");
		std::regex vertexBlockEnd("^\\s+</source>");
		std::regex triangleBlockEnd("^\\s+</triangles>");

		std::regex floatRegex("[+-]*[0-9]+[.]{0,1}[0-9]*");
		std::regex intRegex("[0-9]+");
		
		//Material regex
		std::regex matNameRegex("[a-zA-Z0-9]+[-]{1}effect");

		std::string line;
		std::smatch match;
		
		FileLoader fl;
		
		//Handle the file
		fl.openFile(filePath);
		
		while (fl.hasNextLine())
		{
			fl.readLine(line);

			//Load materials into the mesh
			if (std::regex_match(line, materialBlockStart))
			{
				while(fl.hasNextLine() && !regex_match(line, materialBlockEnd))
				{
					//Add a new material
					if (line.find("effect id=") != std::string::npos)
					{
						std::regex_search(line, match, matNameRegex);
						std::string matName = match[0];
						matName = std::regex_replace(matName, std::regex("effect"), "material");
						materials.push_back(Material(matName));

						//Load the material properties
						while (line.find("</effect>") == std::string::npos)
						{
							if (line.find("sid=\"emission\"") != std::string::npos)
								processMatProp4f(line, materials.back().emission);
							else if (line.find("sid=\"ambient\"") != std::string::npos)
								processMatProp4f(line, materials.back().ambient);
							else if (line.find("sid=\"diffuse\"") != std::string::npos)
								processMatProp4f(line, materials.back().diffuse);
							else if (line.find("sid=\"specular\"") != std::string::npos)
								processMatProp4f(line, materials.back().specular);
							else if (line.find("sid=\"shininess\"") != std::string::npos)
							{
								std::smatch match;
								std::string s;
								std::regex floatRegex("[+-]*[0-9]+[.]{0,1}[0-9]*");
								removeExponents(line);
								removeOpeningTag(line);
								std::regex_search(line, match, floatRegex);
								s = match[0];
								materials.back().shininess = std::strtof(s.c_str(), NULL);
							}
							fl.readLine(line);
						}//Material properties complete
					}//Material is completely read
					fl.readLine(line);
				}
			}//All materials loaded
			
			 //Load vertices into the mesh
			else if (std::regex_match(line, vertexBlockStart))
			{
				while (fl.hasNextLine() && !regex_match(line, vertexBlockEnd))
				{
					if (line.find("-positions-array\"") != std::string::npos)
					{
						removeExponents(line);
						removeOpeningTag(line);
						std::string s;
						while (regex_search(line, match, floatRegex))
						{
							s = match[0];
							vertices.push_back(strtof(s.c_str(), NULL));
							transVerts.push_back(strtof(s.c_str(), NULL));
							line = std::regex_replace(line, floatRegex, "", std::regex_constants::format_first_only);
						}
					}
					fl.readLine(line);
				}
			}//All vertices loaded

			//Load indices into  material
			else if (std::regex_match(line, triangleBlockStart))
			{
				std::regex triangleMatRegex("^\\s+<triangles.+material.+>");
				std::regex triangleMatNameRegex("[a-zA-Z0-9]+[-]{1}material");
				int index = 0;

				while (fl.hasNextLine() && !regex_match(line, triangleBlockEnd))
				{
					//Find out which material this set of triangles belongs to
					if (std::regex_match(line, triangleMatRegex))
					{
						std::regex_search(line, match, triangleMatNameRegex);
						std::string s = match[0];
						
						while (index < materials.size())
						{
							//if the correct material is found, break the loop
							assert(index < materials.size());
							if (s.find(materials[index].matID) != std::string::npos)
								break;
							index++;
						}
					}

					//Read the indeces into the material
					else if (line.find("<p>") != std::string::npos)
					{
						removeOpeningTag(line);
						std::string s;
						while (regex_search(line, match, intRegex))
						{
							s = match[0];
							assert(index < materials.size());
							materials[index].indices.push_back(strtof(s.c_str(), NULL));
							line = std::regex_replace(line, intRegex, "", std::regex_constants::format_first_only);
//TODO: Process normals
							line = std::regex_replace(line, intRegex, "", std::regex_constants::format_first_only);
						}
					}
					fl.readLine(line);
				}
			}
		}
		fl.closeFile();
	}

	//Mesh must be loaded prior to use
	void Mesh::genBufs()
	{
		vertBuf = new VertexBuffer(vertices, GL_DYNAMIC_DRAW);
		for (int i = 0; i < materials.size(); i++)
			materials[i].genBufs();
	}

	void Mesh::processMatProp4f(std::string &line, float f[4])
	{
		std::smatch match;
		std::string s;
		std::regex floatRegex("[+-]*[0-9]+[.]{0,1}[0-9]*");
		removeExponents(line);
		removeOpeningTag(line);
		for(int i=0; i<4; i++)
		{
			std::regex_search(line, match, floatRegex);
			f[i] = strtof(match[0].str().c_str(), NULL);
			line = std::regex_replace(line, floatRegex, "", std::regex_constants::format_first_only);
		}
	}

	void Mesh::removeOpeningTag(std::string &line)
	{
		std::regex stripRegex("^\\s+<(p|.+\")>");
		line = std::regex_replace(line, stripRegex, "", std::regex_constants::format_first_only);
	}

	//Assumes any number in scientific notation is 0
	void Mesh::removeExponents(std::string &line)
	{
		std::regex stripRegex("[+-]*[0-9]+[.]{0,1}[0-9]*[e]{1}[-]{1}[0-9]+");
		line = std::regex_replace(line, stripRegex, "0");
	}

	void Mesh::srt(float sin, Mat4x4<float> min)
	{
		for (int i = 0; i < vertices.size(); i++)
			transVerts[i] = vertices[i] * sin;
		for (int i = 0; i < vertices.size(); i++)
		{
			Vec3D<float> verts(transVerts[i], transVerts[i + 1], transVerts[i + 2]);
			verts = min * verts;
			transVerts[i] = verts.getX();
			transVerts[++i] = verts.getY();
			transVerts[++i] = verts.getZ();
		}
		vertBuf->update(transVerts);
	}
}