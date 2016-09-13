using UnityEngine;
using System.Collections;

public class ModelLoader : MonoBehaviour {
    GameObject obj;

    Rect model1, model2, model3;
    const int OPTXPOS = 1200;
    const int OPTYPOS = 400;
    int optSize = 150;
    int offset = 208;
    bool model1Load = false, model2Load = false, model3Load = false;
    public bool getLoadModel1() { return model1Load; } public void setLoadModel1(bool m1) { model1Load = m1; }
    public bool getLoadModel2() { return model2Load; }  public void setLoadModel2(bool m1) { model2Load = m1; }
    public bool getLoadModel3() { return model3Load; }  public void setLoadModel3(bool m1) { model3Load = m1; }

    // Use this for initialization
    void Start ()
    {
        model1 = new Rect(Screen.width - optSize, OPTYPOS - optSize * 2, optSize, 50);
        model2 = new Rect(Screen.width - optSize, OPTYPOS - optSize, optSize, 50);
        model3 = new Rect(Screen.width - optSize, OPTYPOS, optSize, 50);

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
        }
        if (GUI.Button(model2, "Load model 2"))
        {
            setLoadModel1(false);
            setLoadModel2(true);
            setLoadModel3(false);         
        }
        if (GUI.Button(model3, "Load model 3"))
        {
            setLoadModel1(false);
            setLoadModel2(false);
            setLoadModel3(true);
        }
    }
	// Update is called once per frame
	void Update ()
    {
        if(getLoadModel1())
        {
            Destroy(obj);
            LoadModel("Models/model1");
        }

        if (getLoadModel2())
        {
            Destroy(obj);
            LoadModel("Models/model2");
        }

        if (getLoadModel3())
        {
            Destroy(obj);
            LoadModel("Models/model3");
        }
    }
}
