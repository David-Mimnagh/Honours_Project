using UnityEngine;
using System.Collections;
public class ModelLoader : MonoBehaviour
{
    GameObject obj;
    void LoadModel(string filename)
    {
        obj = (GameObject)Object.Instantiate(Resources.Load(filename));
      
    }
    void Start()
    {
        LoadModel("Models/model2");
    }
}