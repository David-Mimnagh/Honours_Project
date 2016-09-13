using UnityEngine;
using System.Collections;
public class ModelLoader : MonoBehaviour
{
    GameObject obj;

    Renderer renderer;
    Texture model1Texture;

    void LoadModel(string filename)
    {
        obj = (GameObject)Object.Instantiate(Resources.Load(filename));

    }
    void Start()
    {
        LoadModel("Models/model2");

        model1Texture = (Texture)Resources.Load("Textures/Texture2");
        renderer = GameObject.Find("Left_Shoe").GetComponent<Renderer>();
        renderer.material.mainTexture = model1Texture;
        renderer = GameObject.Find("Right_Shoe").GetComponent<Renderer>();
        renderer.material.mainTexture = model1Texture;
    }
}