#include "Application.h"
#include "Primitives/Pyramid.h"
#include "Primitives/Melon.h"
#include <memory>
#include <algorithm>
#include "SimpleMath.h"


Application::Application()
	:
	wnd(800, 600, "Graphics Engine")
{
	class Factory
	{
	public:
		Factory( Graphics& gfx )
			:
			gfx( gfx )
		{}
		std::unique_ptr<Drawable> operator()()
		{
			switch( typedist( rng ) )
			{
			case 0:
				return std::make_unique<Pyramid>(
					gfx,rng,adist,ddist,
					odist,rdist
				);
			case 1:
				return std::make_unique<Box>(
					gfx,rng,adist,ddist,
					odist,rdist,bdist
				);
			case 2:
				return std::make_unique<Melon>(
					gfx, rng, adist, ddist,
					odist, rdist, longdist, latdist);
			default:
				assert( false && "bad drawable type in factory" );
				return {};
			}
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_int_distribution<int> latdist{ 5,20 };
		std::uniform_int_distribution<int> longdist{ 10,40 };
		std::uniform_int_distribution<int> typedist{ 0,2 };
	};

	Factory f( wnd.Gfx() );
	drawables.reserve( nDrawables );
	std::generate_n( std::back_inserter( drawables ),nDrawables,f );

	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

int Application::Go()
{
    while (true)
    {
        if (const auto ecode = Window::ProcessMessages())
        {
            return *ecode;
        }
        DoFrame();
   }
    
}

void Application::DoFrame()
{
	const auto dt = timer.Mark();
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& d : drawables)
	{
		d->Update(dt);
		d->Draw(wnd.Gfx());
	}
	wnd.Gfx().EndFrame();
}
