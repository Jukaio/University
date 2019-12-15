using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy_Controller : MonoBehaviour
{
    public AudioClip clip_;
    AudioSource source_;

    enum Enemy_State
    {
        NOT_HIT,
        HIT,
        VANISH,
    }
    Enemy_State state;

    private void Awake()
    {
        source_ = gameObject.AddComponent<AudioSource>();
        source_.playOnAwake = false;
        source_.clip = clip_;
    }

    private void Update()
    {
        switch (state)
        {
            case Enemy_State.NOT_HIT:

                break;

            case Enemy_State.HIT:
                if (!source_.isPlaying)
                    goto case Enemy_State.VANISH;
                break;

            case Enemy_State.VANISH:
                gameObject.SetActive(false);
                break;
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        other.gameObject.SetActive(false);
        state = Enemy_State.HIT;
        source_.Play();
        gameObject.GetComponent<Collider>().enabled = false;
        gameObject.GetComponent<MeshRenderer>().enabled = false;
    }
}
