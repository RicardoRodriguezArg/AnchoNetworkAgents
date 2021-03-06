#!groovy

pipeline {
    agent any

    stages {
        stage('Building C++ Server - Agent Middleware') {
            steps 
            {
                dir("${env.WORKSPACE}")
                {
                    sh '''#!/bin/bash
                    bazel build --cxxopt='-std=c++2a' //agents_middleware:agents_middleware_server
                    '''
                    echo 'creating target directory for testing'
                    sh 'sudo mkdir -p /usr/bin/agents_middleware_server'
                    sh 'sudo cp ./bazel-bin/agents_middleware/agents_middleware_server /usr/bin/agents_middleware_server/'
                    
                }
            }
            }//End Step 1

            stage('C++ Server - Agent Middleware - All Testing') {

            steps 
            {
                dir("${env.WORKSPACE}")
                {
                    echo 'Testing - Comunication Tests'
                    sh '''#!/bin/bash
                    bazel test --cxxopt='-std=c++2a' //utils/tests:communication_tests
                    '''
                }
            }
            }//End step 2


            stage('Py3 - Building Agent Proxy/Stub x Agents - CLI for Agents') {
                steps {
                    dir("${env.WORKSPACE}")
                    {
                        echo 'Building Python Agent Proxy/Stub x Agents'
                        sh '''#!/bin/bash
                        bazel build //agents_webapi_py/src:agents_cli_app
                        '''
                    }
                }//Step
            }//stage
            
            stage('Py3 - Building Python WebApi x Agents Middleware') {
                steps 
                {
                    dir("${env.WORKSPACE}")
                    {
                        sh '''#!/bin/bash
                        echo 'Building Python webApi x Agents'
                        bazel build //agents_webapi_py/src:agents_webapi_app
                        '''
                    }
                }
            }

            stage('Py3 - Executing Python webApi x Agents Tests') {
                steps {
                    dir("${env.WORKSPACE}")
                    {
                        echo 'Building Python Test webApi'
                        sh '''#!/bin/bash
                        echo 'Py3 - Building Python webApi x Agents - Tests'
                        bazel test //agents_webapi_py/src:agents_webapi_app_tests_suite
                        '''
                    }
                }//steps
            }//Stage
    }//STAGES
}//PIPELINE
