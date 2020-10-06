#pragma once
#include<SFML/Graphics.hpp>
class DCube : public sf::Drawable
{
public:
	DCube()
	{	
		auto a1 = sf::Vector3f(1.0f, 1.0f, 1.0f);   //�о��涥�����ݣ���ʱ��˳��
		auto a2 =sf::Vector3f(-1.0f, 1.0f, 1.0f);
		auto a3 = sf::Vector3f(-1.0f, -1.0f, 1.0f);
		auto a4 = sf::Vector3f(1.0f, -1.0f, 1.0f);
		//ǰ----------------------------  
		
		auto b1 = sf::Vector3f(-1.0f, -1.0f, -1.0f);
		auto b2 = sf::Vector3f(-1.0f, 1.0f, -1.0f);
		auto b3 = sf::Vector3f(1.0f, 1.0f, -1.0f);
		auto b4 = sf::Vector3f(1.0f, -1.0f, -1.0f);
		//��----------------------------  
		
		auto u1 = sf::Vector3f(1.0f, 1.0f, 1.0f);
		auto u2 = sf::Vector3f(1.0f, 1.0f, -1.0f);
		auto u3 = sf::Vector3f(-1.0f, 1.0f, -1.0f);
		auto u4 = sf::Vector3f(-1.0f, 1.0f, 1.0f);
		//��----------------------------  
		
		auto d1 = sf::Vector3f(-1.0f, -1.0f, -1.0f);
		auto d2 = sf::Vector3f(1.0f, -1.0f, -1.0f);
		auto d3 = sf::Vector3f(1.0f, -1.0f, 1.0f);
		auto d4 = sf::Vector3f(-1.0f, -1.0f, 1.0f);
		//��----------------------------  
		
		auto r1 = sf::Vector3f(1.0f, 1.0f, 1.0f);
		auto r2 = sf::Vector3f(1.0f, -1.0f, 1.0f);
		auto r3 = sf::Vector3f(1.0f, -1.0f, -1.0f);
		auto r4 = sf::Vector3f(1.0f, 1.0f, -1.0f);
		//��----------------------------  
		
		auto l1 = sf::Vector3f(-1.0f, -1.0f, -1.0f);
		auto l2 = sf::Vector3f(-1.0f, -1.0f, 1.0f);
		auto l3 = sf::Vector3f(-1.0f, 1.0f, 1.0f);
		auto l4 = sf::Vector3f(-1.0f, 1.0f, -1.0f);

		sf::Vertex(l4);
	}
	
private:
	sf::VertexArray cube;


};

