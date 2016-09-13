using UnityEngine;
using System.Collections;
using System.IO;
public class ModelLoader : MonoBehaviour
{
    Rect model1, model2, model3, write;
    Texture model1Texture, model2Texture, model3Texture;
    GameObject obj;
   
    Renderer renderer;
    const int OPTXPOS = 1200;
    const int OPTYPOS = 400;
    int optSize = 150;
    int offset = 208;
    float[] value;

    bool model1Load = false, model2Load = false, model3Load = false, writetofile = false;
    public bool getLoadModel1() { return model1Load; }
    public void setLoadModel1(bool m1) { model1Load = m1; }
    public bool getLoadModel2() { return model2Load; }
    public void setLoadModel2(bool m1) { model2Load = m1; }
    public bool getLoadModel3() { return model3Load; }
    public void setLoadModel3(bool m1) { model3Load = m1; }

    public bool getwritetoFile() { return writetofile; }
    public void setwritetoFile(bool w) { writetofile = w; }
    // Use this for initialization
    void Start()
    {
        model1 = new Rect(Screen.width - optSize, OPTYPOS - optSize * 2, optSize, 50);
        model2 = new Rect(Screen.width - optSize, OPTYPOS - optSize, optSize, 50);
        model3 = new Rect(Screen.width - optSize, OPTYPOS, optSize, 50);
        write = new Rect(Screen.width / 2 - optSize, OPTYPOS, optSize, 50);
        model1Texture = (Texture)Resources.Load("Textures/Texture1");
        model2Texture = (Texture)Resources.Load("Textures/Texture2");
        model3Texture = (Texture)Resources.Load("Textures/Texture3");
        value = new float[4];
    }
    void writeToFile(string filename, float[] value)
    {
        value[0] = 1.0f;
        value[1] = 1.8f;
        value[2] = 0.3f;
        value[3] = 4.0f;
        using (StreamWriter sw = new StreamWriter(filename, true))  // True to append data to the file; false to overwrite the file
        {
            sw.WriteLine(value[0] + "," + value[1] + "," + value[2] + "," + value[3]);
        }
    }

    void LoadModel(string filename)
    {
        obj = (GameObject)Object.Instantiate(Resources.Load(filename));
    }
    void OnGUI()
    {
        if (GUI.Button(model1, "Load model 1"))
        {
            setLoadModel1(true);
            setLoadModel2(false);
            setLoadModel3(false);

            Debug.Log("Loaded model 1");

        }
        if (GUI.Button(model2, "Load model 2"))
        {
            setLoadModel1(false);
            setLoadModel2(true);
            setLoadModel3(false);
            Debug.Log("Loaded model 2");

        }
        if (GUI.Button(model3, "Load model 3"))
        {
            setLoadModel1(false);
            setLoadModel2(false);
            setLoadModel3(true);
            Debug.Log("Loaded model 3");
        }
        if (GUI.Button(write, "Write Info to file"))
        {
            setwritetoFile(true);
        }
    }
    // Update is called once per frame
    void Update()
    {


        if (getwritetoFile())
        {
            writeToFile("Info.txt", value);
            setwritetoFile(false);
        }
        if (getLoadModel1())
        {
            Destroy(obj);
            LoadModel("Models/model1");
            renderer = GameObject.Find("Jacket 1").GetComponent<Renderer>();
            renderer.material.mainTexture = model1Texture;
            setLoadModel1(false);
        }

        if (getLoadModel2())
        {
            Destroy(obj);
            LoadModel("Models/model2");
            renderer = GameObject.Find("Left_Shoe").GetComponent<Renderer>();
            renderer.material.mainTexture = model2Texture;
            renderer = GameObject.Find("Right_Shoe").GetComponent<Renderer>();
            renderer.material.mainTexture = model2Texture;
            setLoadModel2(false);
        }

        if (getLoadModel3())
        {
            Destroy(obj);
            LoadModel("Models/model3");
            renderer = GameObject.Find("TShirt").GetComponent<Renderer>();
            renderer.material.mainTexture = model3Texture;
            renderer = GameObject.Find("TShirt").GetComponent<Renderer>();
            renderer.material.mainTexture = model3Texture;
            setLoadModel3(false);
        }
    }
}
