#include "Mesh.h"

namespace ssfw
{
	//Default constructor
	Mesh::Mesh()
	{
	}//end Mesh() constructor

	//Default destructor
	Mesh::~Mesh()
	{
		materials.~vector();
	}//end ~Mesh() destructor

	//This method loads the mesh from the location designated in the filePath variable
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
						removeOpeningTag(line);

						char* p = (char*)line.c_str();
						char* end;
						for (float f = std::strtof(p, &end); p != end; f = std::strtof(p, &end))
						{
							p = end;
							if (errno == ERANGE)
							{
								Logger::printErrMsg("Error Reading Vertices!", 5);
								errno = 0;
							}
							vertices.push_back(f);
						}
					}
					fl.readLine(line);
				}
			}//All vertices loaded

			 //Load normals into the mesh
			else if (std::regex_match(line, vertexBlockStart))
			{
				while (fl.hasNextLine() && !regex_match(line, vertexBlockEnd))
				{
					if (line.find("-normals-array\"") != std::string::npos)
					{
						removeOpeningTag(line);

						char* p = (char*)line.c_str();
						char* end;
						for (float f = std::strtof(p, &end); p != end; f = std::strtof(p, &end))
						{
							p = end;
							if (errno == ERANGE)
							{
								Logger::printErrMsg("Error Reading Normals!", 5);
								errno = 0;
							}
							normals.push_back(f);
						}
					}
					fl.readLine(line);
				}
			}//All normals loaded

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
						char* p = (char*)line.c_str();
						char* end;
						int i = 0;
						for (float f = std::strtof(p, &end); p != end; f = std::strtof(p, &end))
						{
							p = end;
							if (errno == ERANGE)
							{
								Logger::printErrMsg("Error Reading Indices!", 5);
								errno = 0;
							}
							if(i % 2 == 0)
								materials[index].indices.push_back((unsigned int)f);
							i++;
						}
					}
					fl.readLine(line);
				}
			}
		}
		fl.closeFile();
	}

	//Generates the vertex and index buffers for the vertices, normals, and materials associated with this model.
	//Mesh must be loaded prior to use
	void Mesh::genBufs()
	{
		vertBuf = new VertexBuffer(vertices, GL_DYNAMIC_DRAW);
		//normBuf = new VertexBuffer(normals, GL_DYNAMIC_DRAW);
		for (int i = 0; i < materials.size(); i++)
			materials[i].genBufs();
	}//end void genBufs() method

	void Mesh::processMatProp4f(std::string &line, float f[4])
	{
		std::smatch match;
		std::string s;
		std::regex floatRegex("[+-]*[0-9]+[.]{0,1}[0-9]*");
		removeOpeningTag(line);
		for(int i=0; i<4; i++)
		{
			std::regex_search(line, match, floatRegex);
			f[i] = strtof(match[0].str().c_str(), NULL);
			line = std::regex_replace(line, floatRegex, "", std::regex_constants::format_first_only);
		}
	}//end void processMatProp4f(std::string &line, float[4]) method

	void Mesh::removeOpeningTag(std::string &line)
	{
		std::regex stripRegex("^\\s+<(p|.+\")>");
		line = std::regex_replace(line, stripRegex, "", std::regex_constants::format_first_only);
	}//end void removeOpeningTag(&std::string) method
}