
using UnityEngine;
using System.Collections;

public class GameManagerScript : MonoBehaviour
{

    public bool atMenu = true;
    public bool isPlaying = false;
    public bool atLooseScreen = false;
    public bool isPaused = false;
    public bool pauseScreen = false;

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
        isPaused = false;
        Screen.showCursor = false;
	}
	
	// Update is called once per frame
	void Update ()
	{
	    if (PlayerScript.isDead)
	    {
	        isPlaying = false;
	        atLooseScreen = true;
            Screen.showCursor = true;
	    }

        //pause screen stuff
        if (Input.GetKeyDown(KeyCode.Escape) && !atMenu)
        {
            pauseScreen = true;
            isPlaying = false;
        }

        //pause screen stuff
        if (Input.GetKeyDown(KeyCode.Escape) && isPaused && !atMenu)
        {
            isPaused = false;
            isPlaying = true;
            pauseScreen = false;
        }
	}

    void OnGUI()
    {
        //display menu stuffs
        if (atMenu)
        {
            Screen.showCursor = true;
            GUI.Box(new Rect(0, 0, Screen.width, Screen.height), "", background);
            GUI.Label(new Rect(Screen.width / 2 * .70f, 25, 100, 150), "Caster Training", style);

            if (GUI.Button(new Rect(Screen.width / 2 * .90f, Screen.height / 2, 250, 150), "Play", style))
            {
                atMenu = false;
                isPlaying = true;
                StartGame();
            }
        }

        //pause menu stuff
        if (pauseScreen && !atMenu)
        {
            isPaused = true;

            if (GUI.Button(new Rect(Screen.width / 2 - 35, Screen.height / 2 - 100, 100, 100), "Resume", style))
            {
                isPlaying = true;
                isPaused = false;
                pauseScreen = false;
            }

            if(GUI.Button(new Rect(Screen.width / 2 - 35, Screen.height / 2 - 25, 100, 100), "Restart", style))
            {
                Application.LoadLevel(0);
            }

            if (GUI.Button(new Rect(Screen.width / 2 - 35, Screen.height / 2 + 50, 100, 100), "Quit", style))
            {
                Application.Quit();
            }
        }

        //if you lose! hahahahahahaha
        if (atLooseScreen)
        {
            Screen.showCursor = true;
            GUI.Label(new Rect(Screen.width / 2 * .50f, Screen.height / 2, 200, 200), "You have failed. Your Score: " + Score, style);

            if(GUI.Button(new Rect( Screen.width / 2 * .75f, Screen.height / 2 + 100, 100, 100), "Play Again", style))
            {
                Application.LoadLevel(0);
            }
        }
    }

    void StartGame()
    {
        GameObject.FindGameObjectWithTag("Player").SendMessage("StartGame");
        GameObject.FindGameObjectWithTag("EnemyManager").SendMessage("StartGame");
    }
}
