using UnityEngine;
using System.Collections;

public class PlayerScript : MonoBehaviour 
{
	public static int Health;
	public static int Score;

	public GUIStyle style;

	// Use this for initialization
	void Start () 
	{
		Health = 100;
	}
	
	// Update is called once per frame
	void Update ()
	{

		if (Health < 0)
		{
			Debug.Log ("DEAD");
		}
	}

	void OnGUI()
	{
		GUI.Label(new Rect(Screen.width / 2, 0, 200, 100), "Score: " + Score, style);

        
	}
}
