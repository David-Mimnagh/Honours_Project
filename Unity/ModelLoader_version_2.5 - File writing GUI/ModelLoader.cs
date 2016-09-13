using UnityEngine;
using System.Collections;
using System.IO;
public class ModelLoader : MonoBehaviour
{
    Rect write;
    const int OPTXPOS = 1200;
    const int OPTYPOS = 400;
    int optSize = 150;
    int offset = 208;

    float[] value;
    bool writetofile = false;
    string file; 
    string fileData = "0";

    public bool getwritetoFile() { return writetofile; }
    public void setwritetoFile(bool w) { writetofile = w; }

    // Use this for initialization
    void Start()
    {
        write = new Rect(Screen.width / 2 - optSize, OPTYPOS, optSize, 50);
        value = new float[4];
        value[0] = 100f;
        value[1] = 10031f;
        value[2] = 14100f;
        value[3] = 1400f;
        file = "info.csv";
    }
    void writeToFile(string filename, float[] value)
    {
        using (StreamWriter sw = new StreamWriter(filename, true))  // True to append data to the file; false to overwrite the file
        {
            sw.WriteLine("FPS: " + value[0] + "," + "Polygon count: " + value[1] + "," + "Time to Load model: " + value[2] + "," + value[3]);
        }
    }
    void OnGUI()
    {
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
            writeToFile(file, value);
            setwritetoFile(false);
        }
    }
}
