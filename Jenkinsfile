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
                    bazel build --cxxopt='-std=c++2a' //agents_middleware:agents_middleware_server &&
                    ls -ls &&
                    echo 'creating target directory for testing'
                    sudo mkdir -p /usr/bin/agents_middleware/
                    '''
                    sh "ls *.json > listJsonFiles"
                    def files = readFile( "listJsonFiles" ).split( "\\r?\\n" );
                    sh "rm -f listJsonFiles"
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

             stage('Agent Middleware - Creating Deb Package') {

            steps 
            {
                dir("${env.WORKSPACE}/AnchoNet_General_Pipeline_main")
                {
                    echo 'Creating deb package'
                    sh '''#!/bin/bash
                    mkdir -p ./bazel-bin/agents_middleware/agents_middleware_server/DEBIAN &&
                    mkdir -p ./bazel-bin/agents_middleware/agents_middleware_server/usr/local/bin &&
                    cp ./bazel-bin/agents_middleware/agents_middleware_server ./bazel-bin/agents_middleware/agents_middleware_server/usr/local/bin/ &&
                    cp ./deb_package/control ./bazel-bin/agents_middleware/agents_middleware_server/DEBIAN &&
                    cp ./deb_package/postinst ./bazel-bin/agents_middleware/agents_middleware_server/DEBIAN &&
                    dpkg-deb --build agentMiddleWare-Anchonet
                    '''
                }
            }
            }//

            stage('Py3 - Agent Proxy/Stub x Agents - CLI for Agents') {
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
