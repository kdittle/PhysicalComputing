using UnityEngine;
using System.Collections;
using System.IO;
using System.IO.Ports;
using System.Text;

public class PlayerScript : MonoBehaviour 
{
	public static int Health;
	public static int Score;

	public GUIStyle style;

	public Texture2D reticle;
	public Rect reticleRect;

    public Vector2 positionVec;

	public Vector3 lastPos;
	public Vector3 mousePos;
	public float nativeRatio;

    public float checkTimer = 0;
	private SerialPort _serialPort;
	private bool _isPortOpen = false;

	// Use this for initialization
	void Start () 
	{
		float curRatio = (0.0f + Screen.width)/Screen.height;
		transform.localScale.Set(nativeRatio/curRatio, 0.0f, 0.0f);
		Screen.showCursor = false;
		lastPos = Input.mousePosition;

        reticleRect = new Rect(0 - (reticle.width / 2), (Screen.height - 0) - (reticle.height / 2),
                       reticle.width, reticle.height);

		Health = 100;

		string[] ports = SerialPort.GetPortNames();
		
//		foreach (string port in ports)
//		{
//			Console.WriteLine(port);
//		}
		
		_serialPort = new SerialPort(ports[1], 9600);
		_serialPort.Open();
		Debug.Log(_serialPort.PortName);
		Debug.Log(_serialPort.BaudRate);
		Debug.Log(_serialPort.IsOpen);
	}
	
	// Update is called once per frame
	void FixedUpdate ()
	{

        checkTimer++;

		if (checkTimer >= 30) 
		{
			_serialPort.WriteLine ("r");
			
			string value = _serialPort.ReadLine (); //read info
			string[] vec3 = value.Split (','); //get 3 part value from arduino
			
			//vec3[0] holds the brake/backwards value
			if (vec3 [0] != "") 
			{
                positionVec.x = float.Parse(vec3[0]);
			}

			if(vec3 [1] != "")
			{
                positionVec.y = float.Parse(vec3[1]);
			}

            Debug.Log("Serial Checked.");

            checkTimer = 0;
		}

        //mousePos = Input.mousePosition;
		
        //if (mousePos != lastPos)
        //    lastPos = mousePos;


//		if (Health < 0)
//		{
//			Debug.Log ("DEAD");
//		}
	}

	void OnGUI()
	{
		GUI.Label(new Rect(Screen.width / 2, 0, 200, 100), "Score: " + Score, style);


		//guiTexture.texture = reticle;
        //reticleRect = new Rect(mousePos.x - (reticle.width / 2), (Screen.height - mousePos.y) - (reticle.height/2),
        //                       reticle.width, reticle.height);

        reticleRect = new Rect(positionVec.x - (reticle.width / 2), (Screen.height - positionVec.y) - (reticle.height / 2),
                               reticle.width, reticle.height);
		
		GUI.DrawTexture(reticleRect, reticle);
        
	}
}
