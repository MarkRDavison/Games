import re

class ServiceGenerator:
    def __init__(self, _projectName, _namespace, _givenName):
        self.projectName = _projectName
        self.namespace = _namespace
        self.givenName = _givenName
        self.splitName = re.sub( r"([A-Z])", r" \1", self.givenName).split()

        pass

    def generateInterface(self):
        includeGaurd = "INCLUDED_{projectName}_SERVICES_INTERFACES_I_{serviceName}_SERVICE_HPP_".format(projectName=self.projectName.upper(), serviceName="_".join([element.upper() for element in self.splitName]))
        className = "I" + self.givenName

        print("~~~~~~Interface~~~~~")
        
        print("#ifndef " + includeGaurd)
        print("#define " + includeGaurd)
        print()
        print("namespace " +  self.namespace + " {")
        print()
        print("    class {cn}Service {{".format(cn=className))
        print("    protected:")
        print("        virtual ~{cn}Service(void) = 0;".format(cn=className))
        print()
        print("    public:")
        print()
        print("    };")
        print()
        print("    inline {cn}Service::~{cn}Service(void) = default;")
        print()
        print("}")
        print()
        print("#endif // " + includeGaurd)
        pass

    def generateHeader(self):
        includeGaurd = "INCLUDED_{projectName}_SERVICES_{serviceName}_SERVICE_HPP_".format(projectName=self.projectName.upper(), serviceName="_".join([element.upper() for element in self.splitName]))

        print("~~~~~~HEADER~~~~~")

        print("#ifndef " + includeGaurd)
        print("#define " + includeGaurd)
        print()
        print("#include <{project}/Services/Interfaces/I{className}Service.hpp>".format(project=self.projectName, className=self.givenName))
        print()
        print("namespace " +  self.namespace + " {")
        print()
        print()
        print("    class {cn}Service : public I{cn}Service {{".format(cn=self.givenName))
        print("    public:")
        print("        ~{cn}Service(void) override;".format(cn=self.givenName))
        print()
        print("    };")
        print()
        print("}")
        print()
        print("#endif // " + includeGaurd)
        pass

    def generateImplementation(self):
        print("~~~~~~IMPLEMENTATION~~~~~")

        print("#include <{project}/Services/{className}Service.hpp>".format(project=self.projectName, className=self.givenName))
        print()
        print("namespace " +  self.namespace + " {")
        print()
        print("    {cn}Service::~{cn}Service(void) {{".format(cn=self.givenName))
        print()
        print("    }")
        print()
        print("}")
        print()
        pass

    def generateMock(self):
        includeGaurd = "INCLUDED_MOCKS_{projectName}_SERVICES_{serviceName}_SERVICE_MOCK_HPP_".format(projectName=self.projectName.upper(), serviceName="_".join([element.upper() for element in self.splitName]))

        print("~~~~~~MOCK~~~~~")

        print("#ifndef " + includeGaurd)
        print("#define " + includeGaurd)
        print()
        print("#include <{project}/Services/Interfaces/I{className}Service.hpp>".format(project=self.projectName, className=self.givenName))
        print("#include <Utility/TestSignal.hpp>")
        print()
        print("namespace " +  self.namespace + " {")
        print()
        print("    class {cn}ServiceMock : public I{cn}Service {{".format(cn=self.givenName))
        print("    public:")
        print("        ~{cn}ServiceMock(void) override {{}}".format(cn=self.givenName))
        print()
        print("    };")
        print()
        print("}")
        print()
        print("#endif // " + includeGaurd)
        pass

    def generateTests(self):
        print("~~~~~~TESTS~~~~~")
        print()
        print("#include <catch/catch.hpp>")
        print("#include <catch/CatchToString.hpp>")
        print("#include <{project}/Services/{className}Service.hpp>".format(project=self.projectName, className=self.givenName))
        print()
        print("namespace " +  self.namespace + " {")
        print("    namespace " +  self.givenName + "ServiceTests {")
        print()
        print("        struct Package {")
        print()
        print("            Package(void) :")
        print("                service() {")
        print()
        print("            }")
        print()
        print("            {cn}Service service;".format(cn=self.givenName))
        print()
        print("        };")
        print()
        print("        TEST_CASE(\"\", \"[{pr}][Services][{cn}Service]\") {{".format(pr=self.projectName, cn=self.givenName))
        print("            Package package{};")
        print("            REQUIRE(false);")
        print("        }")
        print()
        print("    }")
        print("}")
        print()
        pass

    def generate(self):
        print('Generating service for ' + self.givenName + 'Service in ' + self.projectName)
        self.generateInterface()
        self.generateHeader()
        self.generateImplementation()
        self.generateMock()
        self.generateTests()
        pass

if __name__ == '__main__':
    serviceName = "NeedProviderLocation"



    namespace = "drl"
    projectName = "Driller"
    generator = ServiceGenerator(projectName, namespace, serviceName)
    generator.generate()
