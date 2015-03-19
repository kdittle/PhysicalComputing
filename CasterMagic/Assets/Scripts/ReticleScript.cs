using UnityEngine;
using System.Collections;

public class ReticleScript : MonoBehaviour 
{
    public Texture2D reticle;

    public Vector3 lastPos;
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
        Vector3 mousePos = Input.mousePosition;

        if (mousePos != lastPos)
            lastPos = mousePos;

	    guiTexture.texture = reticle;

        //transform.Translate(new Vector3(mousePos.x, mousePos.y, 0.0f));
        transform.position.Set(mousePos.x, mousePos.y, 0.0f);
    }
}
