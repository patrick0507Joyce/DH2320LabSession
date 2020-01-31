/*********************************************************************
 *  Author  : Himangshu Saikia
 *  Init    : Thursday, October 12, 2017 - 11:11:30
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <labtransformations/cubeanimator.h>

namespace inviwo
{

// The Class Identifier has to be globally unique. Use a reverse DNS naming scheme
const ProcessorInfo CubeAnimator::processorInfo_
{
    "org.inviwo.CubeAnimator",      // Class identifier
    "Cube Animator",                // Display name
    "KTH Labs",                 // Category
    CodeState::Experimental,  // Code state
    Tags::None,               // Tags
};

const ProcessorInfo CubeAnimator::getProcessorInfo() const
{
    return processorInfo_;
}


CubeAnimator::CubeAnimator()
    :Processor()
    // Ports
    , meshIn_("meshIn")
    , meshOut_("meshOut")
    // Properties 
    // For a FloatProperty 
    // variablename(identifier, display name, init value, minvalue, maxvalue)
    , rotationRadius_("rotationRadius", "RotationRadius", 0, 0, 3.14)
    , revolutionRadius_("revolutionRadius", "RevolutionRadius", 0, 0, 6.28)
{
    // Add ports
    addPort(meshIn_);
    addPort(meshOut_);
    
    // Add properties
    addProperty(rotationRadius_);
    addProperty(revolutionRadius_);
}


void CubeAnimator::process()
{
    // Clone the input mesh
    if (!meshIn_.getData()) return;
    auto mesh = meshIn_.getData()->clone();

    // Get the matrix that defines where the mesh is currently
    auto matrix = mesh->getWorldMatrix();
    
    const int rotateDistance = 2;
    float xRotate = abs(rotateDistance * cos(rotationRadius_.get() - 1.57));
    float yRotate = abs(rotateDistance * sin(rotationRadius_.get()));
    
    // Transform the mesh (TODO)
    //moving the cube to a radom place on the  trajetory of revolution
    matrix = glm::translate(vec3(2, 0, -3)) * matrix;
    
    //do the rotation for the cube itself
    matrix = glm::translate(vec3(xRotate, yRotate, 1)) * matrix;
    
    matrix = glm::rotate(revolutionRadius_.get(), vec3(0, 0, 1)) * matrix;
    // Update
    mesh->setWorldMatrix(matrix);
	
    // Set output
    meshOut_.setData(mesh);
}

} // namespace

