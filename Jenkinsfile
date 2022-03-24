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
                         bazel build --sandbox_debug --verbose_failures --cxxopt='-std=c++2a' //agents_middleware:agents_middleware_server
                         
                      '''
                  //bazel build --sandbox_debug --verbose_failures --cxxopt=\\\'-std=c++2a\\\' //agents_middleware:agents_middleware_server
                    
                }
                
            }
        }
        
        
    }
}
