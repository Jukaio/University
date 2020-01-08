using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Custom_Input
{
    KeyCode test;
    public enum Key
    {
        NONE = (int)KeyCode.None,
        A = (int)KeyCode.A,
        D = (int)KeyCode.D,
        S = (int)KeyCode.S,
        W = (int)KeyCode.W,
        One = (int) KeyCode.Alpha1,
        Two = (int)KeyCode.Alpha2,
        Three = (int)KeyCode.Alpha3,
        Space = (int)KeyCode.Space,
    }

    public Queue<Key> input_Queue_ = new Queue<Key>();
    public List<Key> previous_Input = new List<Key>();
    public List<float> previous_Inputs_Timer_ = new List<float>();

    float timer_ = 0.8f;

    public Dictionary<Key, bool> Input_Dictionary_ = new Dictionary<Key, bool>();

    public Custom_Input()
    {
        Input_Dictionary_.Add(Key.A, false);
        Input_Dictionary_.Add(Key.S, false);
        Input_Dictionary_.Add(Key.D, false);
        Input_Dictionary_.Add(Key.W, false);
        Input_Dictionary_.Add(Key.One, false);
        Input_Dictionary_.Add(Key.Two, false);
        Input_Dictionary_.Add(Key.Three, false);
        Input_Dictionary_.Add(Key.Space, false);
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

        if (UnityEngine.Input.GetKey(KeyCode.Alpha1)) if (!input_Queue_.Contains(Key.One)) { input_Queue_.Enqueue(Key.One); previous_Input.Add(Key.One); previous_Inputs_Timer_.Add(timer_); }
        if (UnityEngine.Input.GetKey(KeyCode.Alpha2)) if (!input_Queue_.Contains(Key.Two)) { input_Queue_.Enqueue(Key.Two); previous_Input.Add(Key.Two); previous_Inputs_Timer_.Add(timer_); }
        if (UnityEngine.Input.GetKey(KeyCode.Alpha3)) if (!input_Queue_.Contains(Key.Three)) { input_Queue_.Enqueue(Key.Three); previous_Input.Add(Key.Three); previous_Inputs_Timer_.Add(timer_); }
        if (UnityEngine.Input.GetKey(KeyCode.Space)) if (!input_Queue_.Contains(Key.Space)) { input_Queue_.Enqueue(Key.Space); previous_Input.Add(Key.Space); previous_Inputs_Timer_.Add(timer_); }

        if (input_Queue_.Count == 0) input_Queue_.Enqueue(Key.NONE);
    }

    private void Update_Dictionary()
    {
        Input_Dictionary_[Key.A] = input_Queue_.Contains(Key.A);
        Input_Dictionary_[Key.S] = input_Queue_.Contains(Key.S);
        Input_Dictionary_[Key.D] = input_Queue_.Contains(Key.D);
        Input_Dictionary_[Key.W] = input_Queue_.Contains(Key.W);

        Input_Dictionary_[Key.One] = input_Queue_.Contains(Key.One);
        Input_Dictionary_[Key.Two] = input_Queue_.Contains(Key.Two);
        Input_Dictionary_[Key.Three] = input_Queue_.Contains(Key.Three);
        Input_Dictionary_[Key.Space] = input_Queue_.Contains(Key.Space);
    }

}
