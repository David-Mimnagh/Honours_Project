using UnityEngine;
using System.Collections;
using System.IO;

public class ModelLoader : MonoBehaviour
{
    public const int POLYGON_LEVEL = 2; 


    Rect model1, model2, model3, model4, model5, write;
    Texture model1Texture, model2Texture, model3Texture, model4Texture, model5Texture;
    GameObject obj, infoObj;

    Renderer renderer;
    const int OPTXPOS = 1200;
    const int OPTYPOS = 400;
    int optSize = 150;
    int offset = 208;
    float[] value;


    int nextFrame = 0;
    float currentTimer = 0.0f;
    float currentFrame = 0.0f;
    public float refreshTimer = 0.5f;
    float frameCount = 0.0f;
    float loadTimer = 0.0f;
    bool model1Load = false, model2Load = false, model3Load = false, model4Load = false, model5Load = false, writetofile = false;
    public bool getLoadModel1() { return model1Load; }
    public void setLoadModel1(bool m1) { model1Load = m1; }
    public bool getLoadModel2() { return model2Load; }
    public void setLoadModel2(bool m2) { model2Load = m2; }
    public bool getLoadModel3() { return model3Load; }
    public void setLoadModel3(bool m3) { model3Load = m3; }
    public bool getLoadModel4() { return model4Load; }
    public void setLoadModel4(bool m4) { model4Load = m4; }
    public bool getLoadModel5() { return model5Load; }
    public void setLoadModel5(bool m5) { model5Load = m5; }

    public bool getwritetoFile() { return writetofile; }
    public void setwritetoFile(bool w) { writetofile = w; }
    // Use this for initialization
    void Start()
    {
        model1 = new Rect(Screen.width - optSize, OPTYPOS - optSize - optSize, optSize, 50);
        model2 = new Rect(Screen.width - optSize, OPTYPOS - optSize - optSize + 60, optSize, 50);
        model3 = new Rect(Screen.width - optSize, OPTYPOS - optSize - optSize + 120, optSize, 50);
        model4 = new Rect(Screen.width - optSize, OPTYPOS - optSize - optSize + 180, optSize, 50);
        model5 = new Rect(Screen.width - optSize, OPTYPOS - optSize - optSize + 240, optSize, 50);
        write = new Rect(Screen.width / 2 - optSize, OPTYPOS, optSize, 50);
        if (POLYGON_LEVEL == 1)
        {
            model1Texture = (Texture)Resources.Load("Textures/LOW Polygon Models/Texture1");
            model2Texture = (Texture)Resources.Load("Textures/LOW Polygon Models/Texture2");
            model3Texture = (Texture)Resources.Load("Textures/LOW Polygon Models/Texture3");
            model4Texture = (Texture)Resources.Load("Textures/LOW Polygon Models/Texture3");
            model5Texture = (Texture)Resources.Load("Textures/LOW Polygon Models/Texture3");
        }
        else if(POLYGON_LEVEL == 2)
        {
            model1Texture = (Texture)Resources.Load("Textures/MID Polygon Models/Texture1");
            model2Texture = (Texture)Resources.Load("Textures/MID Polygon Models/Texture2");
            model3Texture = (Texture)Resources.Load("Textures/MID Polygon Models/Texture3");
            model4Texture = (Texture)Resources.Load("Textures/MID Polygon Models/Texture3");
            model5Texture = (Texture)Resources.Load("Textures/MID Polygon Models/Texture3");
        }
        else if (POLYGON_LEVEL == 3)
        {
            model1Texture = (Texture)Resources.Load("Textures/HIGH Polygon Models/Texture1");
            model2Texture = (Texture)Resources.Load("Textures/HIGH Polygon Models/Texture2");
            model3Texture = (Texture)Resources.Load("Textures/HIGH Polygon Models/Texture3");
            model4Texture = (Texture)Resources.Load("Textures/HIGH Polygon Models/Texture3");
            model5Texture = (Texture)Resources.Load("Textures/HIGH Polygon Models/Texture3");
        }
        value = new float[4];
        value[0] = 1.0f;
        value[1] = 1.8f;
        value[2] = 0.3f;
        value[3] = 4.0f;
    }
    void writeToFile(string filename, float[] value)
    {
        using (StreamWriter sw = new StreamWriter(filename, true))  // True to append data to the file; false to overwrite the file
        {
			sw.WriteLine(value[0] +  "," + value[1] + "," + value[3]);
        }
    }

    void LoadModel(string filename)
    {
        loadTimer += Time.deltaTime;
        obj = (GameObject)Object.Instantiate(Resources.Load(filename));
        value[3] = loadTimer;
        loadTimer = 0.0f;
    }
    void OnGUI()
    {
        if (GUI.Button(model1, "Load model 1"))
        {
            setLoadModel1(true);
            setLoadModel2(false);
            setLoadModel3(false);
            setLoadModel4(false);
            setLoadModel5(false);
            Debug.Log("Loaded model 1");

        }
        if (GUI.Button(model2, "Load model 2"))
        {
            setLoadModel1(false);
            setLoadModel2(true);
            setLoadModel3(false);
            setLoadModel4(false);
            setLoadModel5(false);
            Debug.Log("Loaded model 2");

        }
        if (GUI.Button(model3, "Load model 3"))
        {
            setLoadModel1(false);
            setLoadModel2(false);
            setLoadModel3(true);
            setLoadModel4(false);
            setLoadModel5(false);
            Debug.Log("Loaded model 3");
        }
        if (GUI.Button(model4, "Load model 4"))
        {
            setLoadModel1(false);
            setLoadModel2(false);
            setLoadModel3(false);
            setLoadModel4(true);
            setLoadModel5(false);
            Debug.Log("Loaded model 3");
        }
        if (GUI.Button(model5, "Load model 5"))
        {
            setLoadModel1(false);
            setLoadModel2(false);
            setLoadModel3(false);
            setLoadModel4(false);
            setLoadModel5(true);
            Debug.Log("Loaded model 3");
        }
        if (GUI.Button(write, "Write Info to file"))
        {
            setwritetoFile(true);
        }
    }
    void FPS()
    {
        if (currentTimer < refreshTimer)
        {
            currentTimer += Time.deltaTime;
            nextFrame++;
        }
        else
        {
            //This code will break if you set your refreshTimer to 0, which makes no sense.
            currentFrame = (float)nextFrame / currentTimer;
            nextFrame = 0;
            currentTimer = 0.0f;
        }
    }
    // Update is called once per frame
    void Update()
    {
        frameCount = Time.frameCount;
        FPS();
        value[0] = currentFrame;
        value[2] = frameCount;
        if (getwritetoFile())
        {
			writeToFile("TestUnityMIDPOLYGON.csv", value);
            setwritetoFile(false);
        }
        if (getLoadModel1())
        {
            Destroy(obj);
            Destroy(infoObj);

            if(POLYGON_LEVEL == 1)
            LoadModel("Models/LOW Polygon Models/model1");
            else if(POLYGON_LEVEL == 2)
                LoadModel("Models/MID Polygon Models/model1");
            else if (POLYGON_LEVEL == 3)
                LoadModel("Models/HIGH Polygon Models/model1");

            foreach (Renderer variableName in GetComponents<Renderer>())
            {
                renderer.material.mainTexture = model1Texture;
            }
            foreach (Renderer variableName in GetComponentsInChildren<Renderer>())
            {
                renderer.material.mainTexture = model1Texture;
            }
            value[1] = 1.0f;
            setLoadModel1(false);
        }

        if (getLoadModel2())
        {
            Destroy(obj);
            Destroy(infoObj);

            if (POLYGON_LEVEL == 1)
                LoadModel("Models/LOW Polygon Models/model2");
            else if (POLYGON_LEVEL == 2)
                LoadModel("Models/MID Polygon Models/model2");
            else if (POLYGON_LEVEL == 3)
                LoadModel("Models/HIGH Polygon Models/model2");

            foreach (Renderer variableName in GetComponentsInChildren<Renderer>())
            {
                renderer.material.mainTexture = model2Texture;
            }
            value[1] = 2.0f;
            setLoadModel2(false);
        }

        if (getLoadModel3())
        {
            Destroy(obj);
            Destroy(infoObj);

            if (POLYGON_LEVEL == 1)
                LoadModel("Models/LOW Polygon Models/model3");
            else if (POLYGON_LEVEL == 2)
                LoadModel("Models/MID Polygon Models/model3");
            else if (POLYGON_LEVEL == 3)
                LoadModel("Models/HIGH Polygon Models/model3");

            foreach (Renderer variableName in GetComponentsInChildren<Renderer>())
            {
                renderer.material.mainTexture = model3Texture;
            }
            value[1] = 3.0f;
            setLoadModel3(false);
        }
        if (getLoadModel4())
        {
            Destroy(obj);
            Destroy(infoObj);

            if (POLYGON_LEVEL == 1)
                LoadModel("Models/LOW Polygon Models/model4");
            else if (POLYGON_LEVEL == 2)
                LoadModel("Models/MID Polygon Models/model4");
            else if (POLYGON_LEVEL == 3)
                LoadModel("Models/HIGH Polygon Models/model4");

            foreach (Renderer variableName in GetComponentsInChildren<Renderer>())
            {
                renderer.material.mainTexture = model4Texture;
            }
            value[1] = 4.0f;
            setLoadModel4(false);
        }
        if (getLoadModel5())
        {
            Destroy(obj);
            Destroy(infoObj);

            if (POLYGON_LEVEL == 1)
                LoadModel("Models/LOW Polygon Models/model5");
            else if (POLYGON_LEVEL == 2)
                LoadModel("Models/MID Polygon Models/model5");
            else if (POLYGON_LEVEL == 3)
                LoadModel("Models/HIGH Polygon Models/model5");

            foreach (Renderer variableName in GetComponentsInChildren<Renderer>())
            {
                renderer.material.mainTexture = model5Texture;
            }
            value[1] = 5.0f;
            setLoadModel5(false);
        }
    }
}
