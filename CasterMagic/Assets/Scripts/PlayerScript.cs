using UnityEngine;
using System.Collections;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Collections.Generic;

public class PlayerScript : MonoBehaviour
{
    public static int Health;
    public static int Score;
    public static bool isDead;
    public bool isPlaying = false;

    public float distance;

    public GameObject PlayerArm;
    public Quaternion PlArmIdentity;
    public GUIStyle style;
    public GameObject Spell;
    private GameObject CastingSpell;
    private GameObject TempSpell;

    public List<GameObject> enemies;
    public GameObject selectedEnemy;

    public Texture2D reticle;
    public Rect retRect;

    public bool isCharging = false;
    public float nativeRatio;

    public float checkTimer = 0;
    private SerialPort _serialPort;
    private bool _isPortOpen = false;

    // Use this for initialization
    void Start()
    {
        Screen.showCursor = false;
        isPlaying = false;

        Health = 100;
        isDead = false;

        PlArmIdentity = PlayerArm.transform.rotation;

        Instantiate(Spell, PlayerArm.transform.GetChild(0).position, Quaternion.identity);

        CastingSpell = GameObject.FindGameObjectWithTag("Spell");

        //tempParticle = Instantiate(particle, new Vector3(transform.position.x, transform.position.y, transform.position.z + distance), Quaternion.identity) as GameObject;

        //        string[] ports = SerialPort.GetPortNames();

        ////		foreach (string port in ports)
        ////		{
        ////			Console.WriteLine(port);
        ////		}

        //        _serialPort = new SerialPort(ports[1], 9600);
        //        _serialPort.Open();
        //        Debug.Log(_serialPort.PortName);
        //        Debug.Log(_serialPort.BaudRate);
        //        Debug.Log(_serialPort.IsOpen);
    }

    // Update is called once per frame
    void Update()
    {
        #region Old Code
        //checkTimer++;

        //if (checkTimer >= 30) 
        //{
        //    _serialPort.WriteLine ("r");

        //    string value = _serialPort.ReadLine (); //read info
        //    string[] vec3 = value.Split (','); //get 3 part value from arduino

        //    //vec3[0] holds the brake/backwards value
        //    if (vec3 [0] != "") 
        //    {
        //        positionVec.x = float.Parse(vec3[0]);
        //    }

        //    if(vec3 [1] != "")
        //    {
        //        positionVec.y = float.Parse(vec3[1]);
        //    }

        //    Debug.Log("Serial Checked.");

        //    checkTimer = 0;
        //}

        //if (isCharging)
        //{
        //    Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        //    Vector3 pos = ray.GetPoint(distance);
        //    CastingSpell.particleSystem.transform.position = pos;
        //}

        //if (Input.GetMouseButtonDown(0))
        //{

        //    CastingSpell.gameObject.particleSystem.Play();

        //    isCharging = true;
        //}

        //if (Input.GetMouseButtonUp(0))
        //{
        //    Spell.rigidbody.AddForce(Vector3.forward * 1000);
        //    isCharging = false;
        //}

        //retRect = new Rect(Screen.width - (Screen.width - Input.mousePosition.x) - (reticle.width / 2), (Screen.height - Input.mousePosition.y) - (reticle.height / 2), reticle.width, reticle.height);
        #endregion

        if (Health <= 0)
            isDead = true;

        if (!isDead && isPlaying)
        {
            //find all enemies and add them to this list
            foreach (GameObject t in GameObject.FindGameObjectsWithTag("Enemy"))
            {
                //check to see if the enemy is on the list already or not
                if (!enemies.Contains(t))
                    enemies.Add(t); //add the new enemy but not the old ones
            }

            //iterate through the list and find out if enemies are missing
            //missing enemies come from them being destoryed.
            //remove these enemies so that targetting can actually take place.
            for (int i = 0; i < enemies.Count; i++)
            {
                if (enemies[i] == null)
                    enemies.Remove(enemies[i]);
            }

            //Target the enemy
            //Allows for space to be pressed multple times to scroll through possible targets

            if (Input.GetKeyDown(KeyCode.Space))
            {
                TargetEnemy();
            }

            //if the mouse button is pressed, the the 
            if (Input.GetKeyDown(KeyCode.Mouse0))
            {
                //main spell stuff
                CastingSpell.particleSystem.transform.position = PlayerArm.transform.GetChild(0).position;
                CastingSpell.gameObject.particleSystem.Play();

                //create the temp spell that will be shot
                TempSpell =
                    Instantiate(CastingSpell, PlayerArm.transform.GetChild(0).position, Quaternion.identity) as
                        GameObject;
            }

            if (Input.GetKeyUp(KeyCode.Mouse0))
            {
                //other casting stuff
                CastingSpell.particleSystem.transform.position = PlayerArm.transform.GetChild(0).position;
                CastingSpell.gameObject.particleSystem.Stop();

                //switch to playing the temp particle
                TempSpell.particleSystem.Play();
                TempSpell.transform.position = PlayerArm.transform.GetChild(0).position;

                //shoot the spell
                TempSpell.rigidbody.AddForce(Vector3.forward*700);
                TempSpell.AddComponent<SphereCollider>();
                TempSpell.collider.enabled = true;
            }

            //have the player arm look at the enemy
            if (selectedEnemy != null)
                PlayerArm.transform.LookAt(selectedEnemy.transform);
            else
                PlayerArm.transform.localRotation = PlArmIdentity;

        }
    }

    void OnGUI()
    {
        if(isPlaying)
            GUI.Label(new Rect(Screen.width / 2, 0, 200, 100), "" + Score, style);
    }

    public void StartGame()
    {
        isPlaying = true;
    }


    public void TargetEnemy()
    {
        //if the selected enemy is null, make the first enemy in the list selected
        if (selectedEnemy == null)
        {
            selectedEnemy = enemies[0];
        }
        else
        {
            //find the index of the current enemy
            int index = enemies.IndexOf(selectedEnemy);

            //increment index every time the target button is pressed
            if (index < enemies.Count - 1)
                index++;
            else
                index = 0;      //reset the index to 0

            selectedEnemy = enemies[index]; //update the selected enemy
        }
    }
}
