#!groovy

pipeline {
    agent any

    stages {
        stage('Building C++ Server - Agent Middleware') {
            steps {
                echo 'Building..'
                dir("${env.WORKSPACE}")
                {
                    sh 'bazel build --cxxopt=\\\'-std=c++2a\\\' //agents_middleware:agents_middleware_server'
                }
                
            }
        }
        
        
    }
}
