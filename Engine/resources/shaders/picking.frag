#version 330 core

uniform uint objectID;

layout(location = 0) out uint outID;

void main()
{
    outID = objectID;
}