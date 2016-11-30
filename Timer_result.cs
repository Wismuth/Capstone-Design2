using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class Timer_result : MonoBehaviour {

    public Text counterText;

    public float seconds, minutes;

	// Use this for initialization
	void Start ()                   // print play time to end page
    {
        counterText = GetComponent<Text>() as Text;
	}
	
	// Update is called once per frame
	void Update () {

        movie.timespan += Time.deltaTime;


        minutes = (int)(movie.timespan / 60f);
        seconds = (int)(movie.timespan % 60f);
        counterText.text = "Time : " + minutes.ToString("00") + ":" + seconds.ToString("00");
	    
	}
}
