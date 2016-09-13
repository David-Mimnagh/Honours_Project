using UnityEngine;
using System.Collections;
using System.IO;
public class ModelLoader : MonoBehaviour
{
    Rect write;
    GameObject obj, infoObj;

    int nextFrame = 0;
    float currentTimer = 0.0f;
    float currentFrame = 0.0f;
    public float refreshTimer = 0.5f;
    float loadTimer = 0.0f;

    const int OPTXPOS = 1200;
    const int OPTYPOS = 400;
    int optSize = 150;
    int offset = 208;

    float[] value;
    bool writetofile = false;


    public bool getwritetoFile() { return writetofile; }
    public void setwritetoFile(bool w) { writetofile = w; }

    // Use this for initialization
    void Start()
    {
        write = new Rect(Screen.width / 2 - optSize, OPTYPOS, optSize, 50);
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
            sw.WriteLine("FPS: " + value[0] + "," + "Polygon count: " + value[1] + "," + "Time to Load model: " + value[2] + "," + value[3]);
        }
    }
    void LoadModel(string filename)
    {
        loadTimer += Time.deltaTime;
        obj = (GameObject)Object.Instantiate(Resources.Load(filename));
        value[2] = loadTimer;
        loadTimer = 0.0f;
    }
    void OnGUI()
    {
        if (GUI.Button(write, "Write Info to file"))
        {
            setwritetoFile(true);
        }
        Debug.Log(loadTimer);
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
            currentFrame = (float)nextFrame / currentTimer;
            nextFrame = 0;
            currentTimer = 0.0f;
        }
    }
    // Update is called once per frame
    void Update()
    {
       
        Destroy(obj);
        Destroy(infoObj);
        
        LoadModel("Models/model1");

        infoObj = GameObject.Find("Jacket 1");
        value[1] = infoObj.GetComponent<MeshFilter>().mesh.triangles.Length / 3;

        FPS();
        value[0] = currentFrame;
        if (getwritetoFile())
        {
            writeToFile("Info.txt", value);
            setwritetoFile(false);
        }
        
    }
}
