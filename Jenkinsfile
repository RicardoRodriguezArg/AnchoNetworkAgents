#!groovy

pipeline {
    agent any

    stages {
        stage('Building C++ Server - Agent Middleware') {
            steps 
            {
                dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                {
                    sh '''#!/bin/bash
                    bazel build --cxxopt='-std=c++2a' //agents_middleware:agents_middleware_server
                    '''
                }
            }
            }//End Step 1

            stage('C++ Server - Agent Middleware - All Testing') {

            steps 
            {
                dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                {
                    echo 'Testing - Comunication Tests'
                    sh '''#!/bin/bash
                    bazel run --cxxopt='-std=c++2a' //utils/tests:communication_tests
                    '''
                }
            }
            }//End step 2

            stage('Py3 - Agent Proxy/Stub x Agents') {
                steps {
                    dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                    {
                        echo 'Building Python Agent Proxy/Stub x Agents'
                        sh '''#!/bin/bash
                        bazel build //agents_webapi_py/src:agents_cli_app
                        '''
                    }
                }//Step
            }//stage
            
            stage('Py3 - Building Python webApi x Agents') {
                steps 
                {
                    dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                    {
                        sh '''#!/bin/bash
                        echo 'Building Python webApi x Agents'
                        bazel build //agents_webapi_py/src:agents_webapi_app
                        '''
                    }
                }
            }

            stage('Py3 - Building Python webApi x Agents - Tests') {
                steps {
                    dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                    {
                        echo 'Building Python webApi x Agents'
                        sh '''#!/bin/bash
                        bazel test //agents_webapi_py/src:agents_webapi_app_tests_suite
                        '''
                    }
                }//steps
            }//Stage
    }//STAGES
}//PIPELINE
