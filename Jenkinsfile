#!groovy

pipeline {
    agent any

    stages {
        stage('Building C++ Server - Agent Middleware') {
            steps {
                echo 'Building..'
                dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                {
                    sh pwd
                    //sh 'bazel build --cxxopt=\\\'-std=c++2a\\\' //agents_middleware:agents_middleware_server'
                }
                
            }
        }
        
        
    }
}
