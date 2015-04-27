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
            GUI.Label(new Rect(Screen.width / 2 * .75f, 25, 100, 150), "Caster Magic", style);

            if (GUI.Button(new Rect(Screen.width/2*.90f, 350, 250, 150), "Play", style))
            {
                atMenu = false;
                isPlaying = true;
                StartGame();
            }
        }

        if (atLooseScreen)
        {
            GUI.Label(new Rect(Screen.width / 2 - 100, Screen.height - 2 - 100, 200, 200), "You have failed. /n Your Score: " + Score, style);

            if(GUI.Button(new Rect( Screen.width / 2 + 100, Screen.height / 2 +100, 250, 250), "Play Again", style))
            {
                Application.LoadLevel(0);
            }
        }
    }

    void StartGame()
    {
        GameObject.FindGameObjectWithTag("Player").SendMessage("StartGame");
    }
}
