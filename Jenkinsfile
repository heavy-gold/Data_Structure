pipeline {
    agent any

    stages {
        stage('Build HashTables') {
            steps {
                // Change directory to where your Makefile is located
                dir('HashTables') {
                    // Use 'bat' for Windows or 'sh' for Linux/Mac
                    // This runs your Makefile to compile the C++ files
                    bat 'make' 
                }
            }
        }
        
        stage('Run Tests') {
            steps {
                dir('HashTables') {
                    echo 'Running Hash Table implementations...'
                    // Replace these with your actual compiled executable names
                    bat 'HashTables_SeparateChaining.exe'
                    bat 'HashTable_LinearProbing.exe'
                }
            }
        }
    }

    post {
        always {
            echo 'Build process complete.'
        }
        success {
            echo 'C++ Data Structures compiled and verified successfully!'
        }
        failure {
            echo 'Build failed. Check the console output for compiler errors.'
        }
    }
}
