from setuptools import setup, find_packages
setup(
    name='autogit',
    version='0.1.3',
    packages=find_packages(),
    install_requires=[

    ],
    entry_points={
        'console_scripts': [
            'autogit = autogit.autogit:main',
        ],
    },
    author='Shazin',
    author_email='shazin.bd@gmail.com',
    description='A simple cli tool for automating basic git jobs',
    url='https://github.com/dev5h/autogit.git',
    license='GPL',
)
