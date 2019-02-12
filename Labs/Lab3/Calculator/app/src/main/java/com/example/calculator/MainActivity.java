package com.example.calculator;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    EditText t1, t2;
    ImageButton plus, minus, multiply,divide;
    TextView displayResult;
    String operator = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        t1 = (EditText) findViewById(R.id.t1);
        t2 = (EditText) findViewById(R.id.t2);

        plus = (ImageButton) findViewById(R.id.plus);
        minus = (ImageButton) findViewById(R.id.minus);
        multiply = (ImageButton) findViewById(R.id.multiply);
        divide = (ImageButton) findViewById(R.id.divide);

        displayResult = (TextView) findViewById(R.id.displayResult);

        // Set listeners
        plus.setOnClickListener(this);
        minus.setOnClickListener(this);
        multiply.setOnClickListener(this);
        divide.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
       double num1 = 0.0;
       double num2 = 0.0;
       double result = 0.0;

       // Check if the fields are empty
        if (TextUtils.isEmpty(t1.getText().toString()) ||
                TextUtils.isEmpty(t2.getText().toString())) {
            return;
        }

        num1 = Float.parseFloat(t1.getText().toString());
        num2 = Float.parseFloat(t2.getText().toString());

        // Perform operations
        // and save the operator for later use
        switch (v.getId()) {
            case R.id.plus:
                operator = "+";
                result = num1 + num2;
                break;
            case R.id.minus:
                operator = "-";
                result = num1 - num2;
                break;
            case R.id.multiply:
                operator = "*";
                result = num1 * num2;
                break;
            case R.id.divide:
                operator = "/";
                result = num1 / num2;
                break;
            default:
                break;
        }

        displayResult.setText(num1 + " " + operator + " " + num2 + " = " + result);
    }
}
