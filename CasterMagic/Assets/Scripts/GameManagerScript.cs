using UnityEngine;
using System.Collections;

public class GameManagerScript : MonoBehaviour
{

    public bool atMenu = true;
    public bool isPlaying = false;
    public bool atLooseScreen = false;

    public int Score;
    public int HighScore;

    public GUIStyle background;
    public GUIStyle style;

    // Use this for initialization
	void Start ()
	{
	    atMenu = true;
	    isPlaying = false;
	    atLooseScreen = false;
	}
	
	// Update is called once per frame
	void Update ()
	{
	    if (PlayerScript.isDead)
	    {
	        isPlaying = false;
	        atLooseScreen = true;
	    }
	}

    void OnGUI()
    {
        //display menu stuffs
        if (atMenu)
        {

            GUI.Box(new Rect(0, 0, Screen.width, Screen.height), "", background);
            GUI.Label(new Rect(Screen.width / 2 * .85f, 25, 500, 150), "Caster Magic", style);
        }

        if (atLooseScreen)
        {
            
        }
    }

    void StartGame()
    {
        GameObject.FindGameObjectWithTag("Player").SendMessage("StartGame");
    }
}
