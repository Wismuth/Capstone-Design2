using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System.IO;
public class movie : MonoBehaviour
{

    public MovieTexture mov;
    public AudioSource aud;
    public static float timespan;
    public float checktime;
    public string logPath = "C:/Users/mobile_lab_01/Documents/Visual Studio 2013/Projects/opencv_0520/opencvex/Release/log.txt";
    //  speed saved file location
    public float speed;
    public float averageSpeed = 20.0f;
    // default average
    public static int count_checktime;
    public static float[] speedarr = new float[1000];
    
    void Start()
    {
        GetComponent<Renderer>().material.mainTexture = mov;
        aud = GetComponent<AudioSource>();

        timespan = 0.0f;
        checktime = 3.0f;
                        
        aud.clip = mov.audioClip;
        aud.pitch = 1.0f;

        mov.Play();
        aud.Play();

    }
    // Update is called once per frame
    void Update()
    {
       try                      //read speed data file
        {
            FileStream file = new FileStream(logPath, FileMode.Open, FileAccess.Read, FileShare.Read);          
            StreamReader sr = new StreamReader(file);
            string str = null;
            str = sr.ReadLine();
            speed = float.Parse(str);
            sr.Dispose();
            Debug.Log(speed);
        }
        catch(IOException e)
        {
             Debug.Log(speed);
        }
        
  
        timespan += Time.deltaTime;             // play time check
        if (Input.GetKey(KeyCode.P) == true || ((mov.isPlaying) && timespan > 530))
        {
            Application.LoadLevel("LastScene");
        }
        if (timespan <= checktime)          // time per speed check   
            return;

        SpeedChange();

    }

    void SpeedChange()
    {
        mov.Pause();                    //speed change start
        aud.Pause();

        checktime += 3.0f;              // every 3 
        count_checktime++;
        speedarr[count_checktime] = speed;              // average speed check array



        aud.pitch = speed / averageSpeed;

        if (aud.pitch >= 2.0f)           // max , min speed control 
        {
            aud.pitch = 2.0f;
        }
        else if (aud.pitch <= 0.2f)
        {
            aud.pitch = 0.2f;
        }


        if (!mov.isPlaying)             //speed change end
        {
            mov.Play();
            aud.Play();
        }
    }     

}
