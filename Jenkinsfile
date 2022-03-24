#!groovy

pipeline {
    agent any

    stages {
        stage('Building C++ Server - Agent Middleware') {
            steps {
                echo 'Building..'
                sh pwd
                sh 'bazel build --verbose_failures --sandbox_debug --cxxopt=\\\'-std=c++2a\\\' //agents_middleware:agents_middleware_server'
            }
        }
        
        
    }
}
