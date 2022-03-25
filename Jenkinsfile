#!groovy

pipeline {
    agent any

    stages {
        stage('Building C++ Server - Agent Middleware')
        {
            steps 
            {
                dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                {
                    sh '''#!/bin/bash
                    bazel build --cxxopt='-std=c++2a' //agents_middleware:agents_middleware_server
                    '''
                }
            }

            steps 
            {
                dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                {
                    echo 'Testing - Comunication Tests'
                    sh '''#!/bin/bash
                    sh 'bazel test --cxxopt=\\"-std=c++2a\\" //utils/tests:communication_tests'
                    '''
                }
            }
            
            
            steps 
            {
                dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                {
                    echo 'Building Python Agent Proxy/Stub x Agents'
                    sh '''#!/bin/bash
                    sh 'bazel build //agents_webapi_py/src:agents_cli_app'
                    '''
                }
            }
            

            steps 
            {
                dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                {
                    sh '''#!/bin/bash
                    echo 'Building Python webApi x Agents'
                    sh 'bazel build //agents_webapi_py/src:agents_webapi_app'
                    '''
                }    
            }

            steps 
            {
                dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                {
                    echo 'Building Python webApi x Agents'
                    sh '''#!/bin/bash
                    sh 'bazel test //agents_webapi_py/src:agents_webapi_app_tests_suite'
                    '''
                }
            }
        }//STAGE
    }//STAGES
}//PIPELINE
