#!groovy

pipeline {
    agent any

    stages {
        stage('Updating Interface data') {
            steps 
            {
                dir("${env.WORKSPACE}/idl_interface")
                {
                    echo 'Executing updating interface scripts - C Nano'
                    
                    sh '''#!/bin/bash
                    chmod +x generate_nano_proto_c_interface.sh
                    ./generate_nano_proto_c_interface.sh
                    '''
                    echo 'Executing updating interface scripts - Python ProtocolBuffer'
                    sh '''#!/bin/bash
                    chmod +x generate_proto_interface.sh
                    ./generate_proto_interface.sh
                    '''
                    
                }
            }
            }//End Step 1

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
                    bazel test --cxxopt='-std=c++2a' //eth_layer/test:eth_layer_tests
                    '''
                }
            }
            }//End step 2

             stage('C++ Agent Middleware - Create Coverage Report') {

            steps 
            {
                dir("${env.WORKSPACE}")
                {
                    echo 'Generating all tests Coverage Report'
                    sh '''#!/bin/bash
                    bazel coverage -s --cxxopt='-std=c++2a' --instrument_test_targets --experimental_cc_coverage --combined_report=lcov --coverage_report_generator=@bazel_tools//tools/test/CoverageOutputGenerator/java/com/google/devtools/coverageoutputgenerator:Main //...
                    mkdir coverage-report
                    genhtml -o coverage-report bazel-out/_coverage/_coverage_report.dat
                    '''
                    // publish html
                    publishHTML target: [
                                         allowMissing: false,
                                         alwaysLinkToLastBuild: false,
                                         keepAll: true,
                                         reportDir: 'coverage-report',
                                         reportFiles: 'index.html',
                                         reportName: 'LCov Report'
                                        ]
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
