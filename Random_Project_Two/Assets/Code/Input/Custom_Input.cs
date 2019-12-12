using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Custom_Input
{
    public enum Mouse
    {
        LEFT_CLICK,
        RIGHT_CLICK,
        X,
        Y,
    }

    public enum Key
    {
        NONE = (int)KeyCode.None,
        A = (int)KeyCode.A,
        D = (int)KeyCode.D,
        S = (int)KeyCode.S,
        W = (int)KeyCode.W,
    }

    public Queue<Key> input_Queue_ = new Queue<Key>();
    public List<Key> previous_Input = new List<Key>();
    public List<float> previous_Inputs_Timer_ = new List<float>();
    public Vector3 mouse_;
    float timer_ = 0.8f;

    public Dictionary<Key, bool> Input_Dictionary_ = new Dictionary<Key, bool>();

    public Custom_Input()
    {
        Input_Dictionary_.Add(Key.A, false);
        Input_Dictionary_.Add(Key.S, false);
        Input_Dictionary_.Add(Key.D, false);
        Input_Dictionary_.Add(Key.W, false);
    }

    public void Init_Keys()
    {

    }

    public float input_on_axis(Key minus, Key plus)
    {
        float temp = 0;

        if (Input_Dictionary_[minus])
            temp += -1;
        if (Input_Dictionary_[plus])
            temp += 1;
        return temp;
    }

    public void Update_Keys()
    {
        Update_Queue();
        Update_Dictionary();
    }

    private void Update_Queue()
    {
        if (UnityEngine.Input.GetKey(KeyCode.A)) if (!input_Queue_.Contains(Key.A)) { input_Queue_.Enqueue(Key.A); previous_Input.Add(Key.A); previous_Inputs_Timer_.Add(timer_); }
        if (UnityEngine.Input.GetKey(KeyCode.D)) if (!input_Queue_.Contains(Key.D)) { input_Queue_.Enqueue(Key.D); previous_Input.Add(Key.D); previous_Inputs_Timer_.Add(timer_); }
        if (UnityEngine.Input.GetKey(KeyCode.S)) if (!input_Queue_.Contains(Key.S)) { input_Queue_.Enqueue(Key.S); previous_Input.Add(Key.S); previous_Inputs_Timer_.Add(timer_); }
        if (UnityEngine.Input.GetKey(KeyCode.W)) if (!input_Queue_.Contains(Key.W)) { input_Queue_.Enqueue(Key.W); previous_Input.Add(Key.W); previous_Inputs_Timer_.Add(timer_); }
        mouse_ = UnityEngine.Input.mousePosition;
        //if (!UnityEngine.Input.GetKey(KeyCode.A)) { input_Queue_.Remove(Key.A); }
        //if (!UnityEngine.Input.GetKey(KeyCode.D)) { input_Queue_.Remove(Key.D); }
        //if (!UnityEngine.Input.GetKey(KeyCode.S)) { input_Queue_.Remove(Key.S); }
        //if (!UnityEngine.Input.GetKey(KeyCode.W)) { input_Queue_.Remove(Key.W); }
        if (input_Queue_.Count == 0) input_Queue_.Enqueue(Key.NONE);
    }

    private void Update_Dictionary()
    {
        Input_Dictionary_[Key.A] = input_Queue_.Contains(Key.A);
        Input_Dictionary_[Key.S] = input_Queue_.Contains(Key.S);
        Input_Dictionary_[Key.D] = input_Queue_.Contains(Key.D);
        Input_Dictionary_[Key.W] = input_Queue_.Contains(Key.W);
    }

}
