using UnityEngine;
using System.Collections;

public class ReticleScript : MonoBehaviour 
{
    public Texture2D reticle;
    public Rect reticleRect;

    public Vector3 lastPos;
    public Vector3 mousePos;
    public float nativeRatio;
    

	// Use this for initialization
	void Start ()
	{
	    float curRatio = (0.0f + Screen.width)/Screen.height;
	    transform.localScale.Set(nativeRatio/curRatio, 0.0f, 0.0f);
	    Screen.showCursor = false;
	    lastPos = Input.mousePosition;
	}
	
	// Update is called once per frame
	void Update () 
    {
        mousePos = Input.mousePosition;

        if (mousePos != lastPos)
            lastPos = mousePos;

        //transform.Translate(new Vector3(mousePos.x, mousePos.y, 0.0f));
        //transform.position.Set(mousePos.x, mousePos.y, 0.0f);
    }

    void OnGUI()
    {
        //guiTexture.texture = reticle;
        reticleRect = new Rect(mousePos.x - (reticle.width / 2), (Screen.height - mousePos.y) - (reticle.height/2),
            reticle.width, reticle.height);

        GUI.DrawTexture(reticleRect, reticle);
    }
}
