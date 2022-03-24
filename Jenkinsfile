#!groovy

pipeline {
    agent any

    stages {
        stage('Building C++ Server - Agent Middleware') {
            steps {
                echo 'Building..'
                dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                {
                   sh '''#!/bin/bash

                         echo "Hello from bash"
                         echo "Who I'm $SHELL"
                         gcc --version
                         
                      '''
                  //bazel build --cxxopt=\\\'-std=c++2a\\\' //agents_middleware:agents_middleware_server
                    
                }
                
            }
        }
        
        
    }
}
