#!groovy

pipeline {
    agent any

    stages {
        stage('Building C++ Server - Agent Middleware') {
            steps {
                echo 'Building..'
                sh 'bazel build --cxxopt=\\\'-std=c++2a\\\' //agents_middleware:agents_middleware_server'
            }
        }
        
        stage('Running C++ Server Tests') {
            steps {
                echo 'Testing - Comunication Tests'
                sh 'bazel test --cxxopt=\\"-std=c++2a\\" //utils/tests:communication_tests'
            }
        }

        stage('Building Python Agent Proxy/Stub x Agents') {
            steps {
                echo 'Building Python Agent Proxy/Stub x Agents'
                
                sh 'bazel build //agents_webapi_py/src:agents_cli_app'
                
            }
        }

        stage('Building Python webApi x Agents') {
            steps {
                echo 'Building Python webApi x Agents'
                
                sh 'bazel build //agents_webapi_py/src:agents_webapi_app'
            }
        }

         stage('Running Python webApi Tests Suite') {
            steps {
                echo 'Building Python webApi x Agents'
                sh 'bazel test //agents_webapi_py/src:agents_webapi_app_tests_suite'
            }
        }
        

        stage('Deploy') {
            steps {
                echo 'No deploy yet'
            }
        }
    }
}
